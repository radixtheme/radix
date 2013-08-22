<?php
/**
 * @file
 * Theme functions
 */

$theme_path = drupal_get_path('theme', 'radix_starter');
require_once $theme_path . '/includes/structure.inc';
require_once $theme_path . '/includes/form.inc';
require_once $theme_path . '/includes/menu.inc';
require_once $theme_path . '/includes/comment.inc';
require_once $theme_path . '/includes/node.inc';

/**
 * Implements hook_css_alter().
 */
function radix_starter_css_alter(&$css) {
  $radix_path = drupal_get_path('theme', 'radix');

  // Radix now includes compiled stylesheets for demo purposes.
  // We remove these from our subtheme since they are already included 
  // in compass_radix.
  unset($css[$radix_path . '/assets/stylesheets/radix-style.css']);
  unset($css[$radix_path . '/assets/stylesheets/radix-print.css']);
}

/**
 * Implements template_preprocess_page().
 */
function radix_starter_preprocess_page(&$variables) {
  // Add copyright to theme.
  if ($copyright = theme_get_setting('copyright')) {
    $variables['copyright'] = check_markup($copyright['value'], $copyright['format']);
  }
}
