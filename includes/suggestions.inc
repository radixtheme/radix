<?php

/**
 * @file
 * Theme suggestions.
 */

use Drupal\node\Entity\Node;

/**
 * Implements hook_theme_suggestions_hook_alter().
 */
function radix_theme_suggestions_page_alter(array &$suggestions, array $variables) {
  // Add a template suggestions for node type.
  /** @var \Drupal\node\NodeInterface $node */
  if ($node = \Drupal::routeMatch()->getParameter('node')) {
    if (is_numeric($node)) {
      $node = Node::load($node);
    }

    $suggestions[] = 'page__node__' . $node->bundle();
  }
}

/**
 * Implements hook_theme_suggestions_hook_alter().
 */
function radix_theme_suggestions_user_alter(array &$suggestions, array $variables) {
  // Add a suggestion based on the view mode.
  $suggestions[] = $variables['theme_hook_original'] . '__' . $variables['elements']['#view_mode'];
}
