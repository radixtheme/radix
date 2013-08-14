<?php
/**
 * @file
 * Theme and preprocess functions for menus
 */

/**
 * Implements theme_menu_tree().
 */
function radix_menu_tree(&$variables) {
  return '<ul class="menu nav">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree__menu_block().
 */
function radix_menu_tree__menu_block(&$variables) {
  return '<ul class="menu nav nav-tabs nav-stacked">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_link().
 */
function radix_menu_link($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if (!empty($element['#below'])) {
    // Wrap in dropdown-menu.
    unset($element['#below']['#theme_wrappers']);
    $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';

    // Check if element is nested.
    if ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] > 1)) {
      $element['#attributes']['class'][] = 'dropdown-submenu';
    }
    else {
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;
      $element['#title'] .= '<span class="caret"></span>';
    }

    $element['#localized_options']['attributes']['data-target'] = '#';
  }

  // Fix for active class.
  if (($element['#href'] == current_path() || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']) || $element['#localized_options']['language']->language == $language_url->language)) {
    $element['#attributes']['class'][] = 'active';
  }

  // Add active class to li if active trail.
  if (in_array('active-trail', $element['#attributes']['class'])) {
    $element['#attributes']['class'][] = 'active';
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_link__management.
 *
 * We render the management links as defaults to support the navbar module
 * out of the box.
 */
function radix_menu_link__management($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_link().
 */
function radix_link($variables) {
  $icons = '';
  if (isset($variables['options']['attributes']['class']) && is_array($variables['options']['attributes']['class'])) {
    $css_classes = $variables['options']['attributes']['class'];
    if ($icon_classes = preg_grep('/^icon\-.*/', $css_classes)) {
      // Render an icon for each class.
      foreach ($icon_classes as $icon_class) {
        $icons .= '<i class="' . $icon_class . '"></i>';
      }
      // Unset icon classes for attributes to prevent double rendering.
      $variables['options']['attributes']['class'] = array_diff($css_classes, $icon_classes);
    }
  }
  return '<a href="' . check_plain(url($variables['path'], $variables['options'])) . '"' . drupal_attributes($variables['options']['attributes']) . '>' . $icons . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a>';
}
