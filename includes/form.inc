<?php
/**
 * @file
 * Theme and preprocess functions for forms
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function radix_form_search_block_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  // Add the navbar-form class.
  $form['#attributes']['class'][] = 'navbar-form';

  // Update the placeholder and size of field.
  $form['keys']['#title'] = '';
  $form['keys']['#size'] = 20;
  $form['keys']['#placeholder'] = t('Search');
}

/**
 * Implements hook_preprocess_input().
 */
function radix_preprocess_input(&$variables) {
  $element = $variables['element'];
  // Add the element type to the theme.
  $variables['type'] = $element['#type'];
}
