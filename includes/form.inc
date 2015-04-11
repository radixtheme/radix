<?php
/**
 * @file
 * Theme and preprocess functions for forms
 */

/**
 * Implements hook_preprocess_input().
 */
function radix_preprocess_input(&$variables) {
  $element = $variables['element'];
  // Add the element type to the theme.
  $variables['type'] = $element['#type'];
}

