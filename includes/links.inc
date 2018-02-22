<?php

/**
 * @file
 * Theme and preprocess functions for links
 */

/**
 * Implements hook_preprocess_links__dropbutton().
 */
function radix_preprocess_links__dropbutton(&$variables) {
  // Make the first link into a button.
  $first_link = array_shift($variables['links']);
  if (!empty($first_link['link'])) {
    $attributes = $first_link['link']['#url']->getOption('attributes') ?: [];
    $attributes['class'][] = 'btn';
    $attributes['class'][] = 'btn-default';
    $first_link['link']['#url']->setOption('attributes', $attributes);
    $variables['first_link'] = $first_link;
  }
}
