<?php

/**
 * Implements HOOK_theme_suggestions_HOOK_alter().
 */
function radix_theme_suggestions_page_alter(array &$suggestions, array $variables) {
  // Add a template suggestions for node type.
  /** @var \Drupal\node\NodeInterface $node */
  if ($node = \Drupal::routeMatch()->getParameter('node')) {
    $suggestions[] = 'page__node__' . $node->bundle();
  }
}
