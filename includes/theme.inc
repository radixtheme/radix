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
      ),
      'function' => 'theme_radix_dropdown',
    ),
  );
}


/**
 * Implements theme_radix_dropdown().
 */
function theme_radix_dropdown($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('dropdown-menu')));

  $output .= '<div class="dropdown">';
  $output .= '<ul' . drupal_attributes($attributes) . '>';

  $num_links = count($links);
  $i = 1;

  foreach ($links as $key => $link) {
    $class = array($key);

    // Add first, last and active classes to the list of links to help out themers.
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
      // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
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
  $output .= '</div>';

  return $output;
}
