up-config-variables provides a drush command to update all configuration
variables of a drupal site in a single step.

The variables should be defined in JSON format, in a configuration file
specific to the site.

The JSON format should be,
  {
    "default": {
      "variable_name1": "value1",
      "variable_name2": "value2"
    }
  }
 
If the variable is a domain variable, then specify the domain id instead
of "default".
