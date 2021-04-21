<?php

/**
 * @file
 * Theme and preprocess functions for forms.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function radix_theme_suggestions_form_alter(array &$suggestions, array &$variables) {
  $element = $variables['element'];

  // Add a suggestion based on the form id name.
  if (isset($element['#form_id'])) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $element['#form_id'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function radix_theme_suggestions_form_element_alter(array &$suggestions, array &$variables) {
  $element = $variables['element'];

  // Add a suggestion based on the element type.
  if (isset($element['#type'])) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $element['#type'];
  }
}

/**
 * Implements hook_preprocess_input().
 */
function radix_preprocess_input(&$variables) {
  $element = $variables['element'];

  // Add the element type to the theme.
  $variables['type'] = $element['#type'];
}

/**
 * Implements hook_preprocess_form_element().
 */
function radix_preprocess_form_element(&$variables) {
  $element = $variables['element'];

  // Add required class for checkbox and radio labels.
  if (in_array($element['#type'], ['checkbox', 'radio'])) {
    $variables['label']['#attributes']['class'][] = 'form-check-label';
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function radix_form_search_block_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  // Update the placeholder and size of field.
  $form['keys']['#title'] = '';
  $form['keys']['#size'] = 20;
  $form['keys']['#placeholder'] = t('Search');
}
