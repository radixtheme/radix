<?php

/**
 * Implements template_preprocess_breadcrumb().
 */
function radix_preprocess_breadcrumb(&$variables) {
  // Add the page title to the breadcrumb.
  $request = \Drupal::request();
  $route_match = \Drupal::routeMatch();
  if ($page_title = \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject())) {
    $variables['breadcrumb'][] = array(
      'text' => $page_title
    );
  }
}
