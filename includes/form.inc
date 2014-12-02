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

/**
 * Implements template_preprocess_links().
 */
function radix_preprocess_links(&$variables) {
  switch ($variables['theme_hook_original']) {
    case 'links__dropbutton':
    case 'links__dropbutton__operations':
      // Get the first link and render it as a button.
      $variables['first_link'] = array_shift($variables['links']);

      if (!empty($variables['first_link']['link'])) {
        $variables['first_link']['link']['#attributes']['class'][] = 'btn';
        $variables['first_link']['link']['#attributes']['class'][] = 'btn-default';
        unset($variables['first_link']['text']);
      }

      // Remove all classes and add bootstrap classes.
      $variables['attributes']['class'] = array('dropdown-menu');
      break;
  }
}
