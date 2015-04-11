<?php
/**
 * @file
 * Theme and preprocess functions for menus
 */

/**
 * Implements hook_preprocess().
 */
function radix_preprocess(&$variables, $hook) {
//  kint($hook);
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

      if (count($item['below'])) {
        $item['url']->setOption('html', TRUE);
      }
    }
  }
}
