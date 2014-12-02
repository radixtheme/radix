<?php
/**
 * @file
 * Theme and preprocess functions for admin.
 */

/**
 * Implements template_preprocess_views_ui_display_tab_setting().
 */
function radix_preprocess_views_ui_display_tab_setting(&$variables) {
  $variables['settings_links'] = str_replace('class="label"', 'class="views-admin-label"', $variables['settings_links']);
}
