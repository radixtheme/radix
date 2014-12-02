<?php
/**
 * @file
 * Theme and preprocess functions for contrib modules.
 */

/**
 * Preprocess function for Date pager template.
 */
function radix_preprocess_date_views_pager(&$variables) {
  // Render pagers controls as buttons.
  $variables['prev_options']['attributes']['class'][] = 'btn';
  $variables['prev_options']['attributes']['class'][] = 'btn-default';
  $variables['next_options']['attributes']['class'][] = 'btn';
  $variables['next_options']['attributes']['class'][] = 'btn-default';
}
