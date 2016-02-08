<?php
/**
 * @file
 * Theme and preprocess functions for block
 */

use Drupal\Core\Render\Element;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function radix_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  // Check for BlockContent.
  if (!empty($variables['elements']['content'])) {
    if (!empty($variables['elements']['content']['#block_content'])) {
      // Get the block bundle.
      $bundle = $variables['elements']['content']['#block_content']->bundle();

      // Add to theme suggestions.
      $suggestions[] = 'block__' . $bundle;
    }
  }
}

/**
 * Implements hook_preprocess_block().
 */
function radix_preprocess_block(&$variables) {
  // Add the css id as class
  $variables['attributes']['class'][] = $variables['attributes']['id'];

  // Check for BlockContent.
  if (!empty($variables['elements']['content'])) {
    if (!empty($variables['elements']['content']['#block_content'])) {
      // Get the block bundle.
      $bundle = $variables['elements']['content']['#block_content']->bundle();
      // Add the block bundle as class.
      $variables['attributes']['class'][] = 'block-type--' . $bundle;
    }
  }
}

/**
 * Implements template_preprocess_block_content().
 */
function radix_preprocess_block_content(&$variables) {
  // Helpful $content variable for templates.
  $variables += array('content' => array());
  foreach (Element::children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }
}
