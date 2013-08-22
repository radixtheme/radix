<?php
/**
 * @file
 * Theme settings.
 */

/**
 * Implements theme_settings().
 */
function radix_starter_form_system_theme_settings_alter(&$form, &$form_state) {
  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('theme', 'radix_starter') . '/theme-settings.php';

  // Add theme settings here.

  // Return the additional form widgets.
  return $form;
}
