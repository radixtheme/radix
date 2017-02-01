<?php
/**
 * @file
 * Theme and preprocess functions for menus
 */

/**
 * Implements hook_preprocess_menu().
 */
function radix_preprocess_menu(&$variables, $hook) {
  // No changes for menu toolbar.
  if ($hook == 'menu__toolbar') {
    return;
  }
  
  // Get the current path.
  $current_path = \Drupal::request()->getRequestUri();

  $items = $variables['items'];
  foreach ($items as $key => $item) {
    // If path is current_path, set active to li.
    if ($item['url']->toString() == $current_path) {
      // Add active link.
      $variables['items'][$key]['attributes']['class'] = 'active';
    }

    if (count($item['below'])) {
      $item['url']->setOption('html', TRUE);
    }
  }
}

/**
 * Implements template_preprocess_menu_local_action().
 */
function radix_preprocess_menu_local_action(&$variables) {
  // Add button classes.
  $variables['link']['#options']['attributes']['class'][] = 'btn';
  $variables['link']['#options']['attributes']['class'][] = 'btn-default';
}
