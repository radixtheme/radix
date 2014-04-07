# Radix

Radix is a base theme for [Panopoly](http://drupal.org/project/panopoly). It has Sass and Compass support, and makes it easy to build responsive themes with Panels.

* Project Page:   http://drupal.org/project/radix
* Documentation:  https://drupal.org/node/1840310
* Demo:           http://dev-radix.gotpantheon.com
* Issue Queue:    http://drupal.org/project/issues/radix

## Maintainer(s): 

* Arshad Chummun
* Capi Etheriel

## Subtheming Guide

1. Install the required gems:

        sudo gem install compass_radix -v 2

  This should install all required gems for Radix.

2. Download the latest Radix and place it in your themes folder.

3. Using drush run the following command to create a subtheme.

        drush radix "SUBTHEME_NAME"

  You can also specify some options when creating your subtheme.

        drush radix "SUBTHEME_NAME" --description="This is the description of subtheme."

  Available options:

        --bootswatch                              The Bootswatch theme to use. See https://github.com/arshad/radix-bootswatch.
        --description                             The description of your subtheme.
        --destination                             The destination of your subtheme. Defaults to "all" (sites/all/themes).
        --kit                                     The name of the starter kit to use. Defaults to "default".
        --machine_name                            The machine-readable name of your subtheme. Auto-generated if ommited.

4. To start making changes to your theme, using a command line cd to your subtheme directory and run:
        
        compass watch

  You can now start adding your Sass to your subtheme.


For more information on subtheming, visit the Radix Handbook at https://drupal.org/node/1840310.

