<?php

/**
 * Drush command file to set up configuration variables.
 */

/**
 * Implements hook_drush_command().
 */
function config_variables_drush_command() {
  $items = array();

  $items['up-config-variables'] = array(
    'description' => 'Update configuration variables.',
    'arguments' => array(
      'config_file_path' => 'Full path to the configuration file, which defines the variables in JSON format',
    ),
    'examples' => array(
      'drush upconfig /home/variables.conf' => 'Update configuration specified in the file.',
    ),
    'aliases' => array('upconfig'),
  );

  return $items;
}

/**
 * Update configuration variables.
 * 
 * @param string config_file_path.
 *   Full path to the configuration file, which defines the variables
 *   in JSON format.
 * 
 * The JSON format should be,
 *  {
 *    "default": {
 *      "variable_name1": "value1",
 *      "variable_name2": "value2"
 *    }
 *  }
 * If the variable is a domain variable, then specify the domain id
 * instead of "default".
 * 
 */
function drush_config_variables_up_config_variables($config_file_path) {
  $conf = file_get_contents($config_file_path);
  if ($conf) {
    $conf_variables = json_decode($conf);
    if ($conf_variables) {
      foreach ($conf_variables as $key => $variables) {
        foreach ($variables as $name => $value) {
          if ($key == 'default') {
            variable_set($name, $value);
            drush_print(dt($name . ' updated on ' . $key));
          }
          elseif ((is_numeric($key))
            && module_exists('domain')
            && module_exists('variable_store')) {
            $realm_key = domain_load_machine_name($key);
            variable_store_set('domain', $realm_key, $name, $value);
            drush_print(dt($name . ' updated on ' . $key));
          }
          else {
            drush_print(dt('Error: ' . $name . ' is not updated on ' . $key));
          }
        }
      }
    }
  }
}
