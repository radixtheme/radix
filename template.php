<?php

/**
 * Implements template_preprocess_page().
 */
function radix_preprocess_page(&$variables) {
  // Search Form
  if (module_exists('search')) {
    $search_form = drupal_get_form('search_block_form');
    $search_form['#attributes']['class'][] = 'search-form';
    $search_form['search_block_form']['#attributes']['placeholder'] = t('Search');
    $variables['search_form'] = render($search_form);
  }
}