#!/bin/bash

### First parameter is the domain name and second parameter is the web-root.
name=$1
WEB_ROOT_DIR=$2

email='webmaster@localhost'
sitesAvailable='/etc/apache2/sites-available/'
sitesAvailabledomain=$sitesAvailable$name.local.conf
echo "Creating a vhost for $name.local with a webroot $WEB_ROOT_DIR"

### create virtual host rules file.
echo "
		<VirtualHost *:80>
			ServerAdmin $email
			ServerName $name.local
			DocumentRoot $WEB_ROOT_DIR
			<Directory $WEB_ROOT_DIR/>
				Options Indexes FollowSymLinks
				AllowOverride all
				Require all granted
			</Directory>
		</VirtualHost>" > $sitesAvailabledomain
echo -e $"\nNew Virtual Host Created\n"

### Add the domain name to hosts file.
sudo sed -i "1s/^/127.0.0.1 $name.local\n/" /etc/hosts

### Enable the site and reload the apache.
sudo a2ensite $name.local.conf
sudo service apache2 reload

echo "Done, please browse to http://$name.local to check!"
