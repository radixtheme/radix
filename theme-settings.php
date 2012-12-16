<?php

/**
* Implements theme_settings().
*
* @param $saved_settings
*   array An array of saved settings for this theme.
* @return
*   array A form array.
*/
function radix_form_system_theme_settings_alter(&$form, &$form_state) {
  
  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('theme', 'radix') . '/theme-settings.php';
  
  $form['radix_settings_title'] = array(
    '#markup' => t('Radix Settings'),
  );
  
  $form['radix_theme_settings'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Radix Theme Settings'),
  );

  // Return the additional form widgets
  return $form;
}
  