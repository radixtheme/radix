<?php
/**
 * @file
 * Theme and preprocess functions for comments
 */

/**
 * Implements template_preprocess_comment().
 */
function radix_preprocess_comment(&$variables) {
  $comment = $variables['comment'];

  // Add proper classes
  $variables['title_attributes_array']['class'][] = 'media-heading';

  // Use icon for permalink
  $uri = entity_uri('comment', $comment);
  $uri['options'] += array('attributes' => array('class' => 'permalink muted pull-right', 'rel' => 'bookmark'), 'html' => TRUE);
  $variables['permalink'] = l('<i class="icon-comment"></i>', $uri['path'], $uri['options']);

  // Use icon for new
  $variables['new'] = !empty($comment->new) ? '<i class="icon-comment"></i>' : '';
}
