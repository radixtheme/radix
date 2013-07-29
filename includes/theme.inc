<?php
/**
 * @file
 * Theme functions for Radix + Bootstrap.
 */

/**
 * Implements hook_theme().
 */
function radix_theme(&$existing, $type, $theme, $path) {
  return array(
    'radix_dropdown' => array(
      'variables' => array(
        'links' => NULL,
        'attributes' => NULL,
        'wrapper' => NULL,
      ),
      'function' => 'theme_radix_dropdown',
    ),
    'radix_button_group' => array(
      'variables' => array(
        'buttons' => NULL,
        'attributes' => NULL,
      ),
      'function' => 'theme_radix_button_group',
    ),
    'radix_button_dropdown' => array(
      'variables' => array(
        'button' => NULL,
        'links' => NULL,
        'split' => NULL,
        'attributes' => NULL,
      ),
      'function' => 'theme_radix_button_dropdown',
    ),
  );
}

/**
 * Implements theme_radix_dropdown().
 */
function theme_radix_dropdown($variables) {
  $links = $variables['links'];
  $attributes = (isset($variables['attributes'])) ? $variables['attributes'] : array();
  $wrapper = (isset($variables['wrapper'])) ? $variables['wrapper'] : FALSE;
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('dropdown-menu')));

  if ($wrapper) {
    $output .= '<div class="dropdown">';
  }
  $output .= '<ul' . drupal_attributes($attributes) . '>';

  $num_links = count($links);
  $i = 1;

  foreach ($links as $key => $link) {
    $class = array($key);

    // Add first, last and active classes to the list of links.
    if ($i == 1) {
      $class[] = 'first';
    }
    if ($i == $num_links) {
      $class[] = 'last';
    }

    // If empty, render as divider.
    if (empty($link)) {
      $output .= '<li class="divider"></li>';
      $i++;
      continue;
    }

    if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
      $class[] = 'active';
    }

    // Add a disabled option.
    if (isset($link['disabled']) && $link['disabled']) {
      $class[] = 'disabled';
    }

    $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

    if (isset($link['href'])) {
      // Pass in $link as $options, they share the same keys.
      $output .= l($link['title'], $link['href'], $link);
    }
    elseif (!empty($link['title'])) {
      // Some links are actually not links,
      // but we wrap these in <span> for adding title and class attributes.
      if (empty($link['html'])) {
        $link['title'] = check_plain($link['title']);
      }
      $span_attributes = '';
      if (isset($link['attributes'])) {
        $span_attributes = drupal_attributes($link['attributes']);
      }
      $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
    }

    $i++;
    $output .= "</li>\n";
  }

  $output .= '</ul>';

  if ($wrapper) {
    $output .= '</div>';
  }

  return $output;
}

/**
 * Implements theme_radix_button_group().
 */
function theme_radix_button_group($variables) {
  $buttons = $variables['buttons'];
  $attributes = $variables['attributes'];
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('btn-group')));

  $output .= '<div' . drupal_attributes($attributes) . '>';

  $num_links = count($buttons);
  $i = 1;

  foreach ($buttons as $key => $button) {
    $class = array($key);
    $class[] = 'btn';

    // Add first, last and active classes to the list of links.
    if ($i == 1) {
      $class[] = 'first';
    }
    if ($i == $num_links) {
      $class[] = 'last';
    }

    // Add Boostrap attributes.
    $button['attributes'] = drupal_array_merge_deep($button['attributes'], array('class' => $class));

    $output .= l($button['title'], $button['href'], $button);

    $i++;
    $output .= "</li>\n";
  }

  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_radix_button_dropdown().
 */
function theme_radix_button_dropdown($variables) {
  $button = $variables['button'];
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $split = $variables['split'];
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('btn-group')));

  $output .= '<div' . drupal_attributes($attributes) . '>';

  // Handle split buttons.
  if ($split) {
    // Add Boostrap attributes.
    $button['attributes'] = drupal_array_merge_deep($button['attributes'], array(
      'class' => array('btn'),
    ));
  }
  else {
    // Add Boostrap attributes.
    $button['attributes'] = drupal_array_merge_deep($button['attributes'], array(
      'class' => array('btn', 'dropdown-toggle'),
      'data-toggle' => 'dropdown',
    ));

    // When split, we do not want the button to have href.
    $button['href'] = '';
    $button['absolute'] = TRUE;
    $button['fragment'] = FALSE;

    // Add caret to title.
    $button['title'] .= '<span class="caret"></span>';
    $button['html'] = TRUE;
  }

  // Render the button.
  $output .= l($button['title'], $button['href'], $button);

  if ($split) {
    // Add a split button.
    $split_attributes = drupal_array_merge_deep($button['attributes'], array(
      'class' => array('btn', 'dropdown-toggle'),
      'data-toggle' => 'dropdown',
    ));
    $output .= '<button ' . drupal_attributes($split_attributes) . '><span class="caret"></span></button>';
  }

  // Render the dropdown menu.
  $output .= theme('radix_dropdown', array('links' => $links));

  $output .= '</div>';
  return $output;
}
