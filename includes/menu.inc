<?php
/**
 * @file
 * Theme and preprocess functions for menus
 */

/**
 * Implements hook_preprocess_menu().
 */
function radix_preprocess_menu(&$variables, $hook) {
  if ($hook == 'menu__main') { // We're doing that for main menu.
    // Get the current path.
    $current_path = \Drupal::request()->getRequestUri();
    $items = $variables['items'];
    foreach ($items as $key => $item) {
      // If path is current_path, set active to li.
      if ($item['url']->toString() == $current_path) {
        // Add active link.
        $variables['items'][$key]['attributes']['class'] = 'active';
      }
    }
  }
}
