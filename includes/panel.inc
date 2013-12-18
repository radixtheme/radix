<?php
/**
 * @file
 * Theme and preprocess functions for panes and panels.
 */

/**
 * Implements template_preprocess_panels_pane().
 */
function radix_preprocess_panels_pane(&$variables) {
  $pane = $variables['pane'];
  if (isset($pane->css['css_class'])) {
    // Check for Bootstrap panel classes.
    $css_classes = explode(" ", $pane->css['css_class']);
    $bootstrap_panel_classes = _radix_get_bootstrap_panel_classes();
    $panel_classes = array_intersect($css_classes, $bootstrap_panel_classes);

    if (count($panel_classes)) {
      // Use a different template.
      $variables['theme_hook_suggestions'][] = 'panels_pane__bootstrap_panel';

      // Add default classes to panel.
      $variables['classes_array'][] = 'panel';
      $variables['classes_array'] += $panel_classes;

      // Add default classes to pane title.
      $variables['title_attributes_array']['class'][] = 'panel-title';
    }
  }
}
