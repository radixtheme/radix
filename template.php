<?php
/**
 * @file
 * Theme hooks for Radix.
 */

require_once dirname(__FILE__) . '/includes/utilities.inc';
require_once dirname(__FILE__) . '/includes/theme.inc';
require_once dirname(__FILE__) . '/includes/structure.inc';
require_once dirname(__FILE__) . '/includes/form.inc';
require_once dirname(__FILE__) . '/includes/menu.inc';
require_once dirname(__FILE__) . '/includes/comment.inc';

/**
 * Implementation of template_preprocess_html().
 */
function radix_preprocess_html(&$variables) {
  // Add meta for Bootstrap Responsive.
  // <meta name="viewport" content="width=device-width, initial-scale=1.0">
  $element = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1.0',
    ),
  );
  drupal_add_html_head($element, 'bootstrap_responsive');
}

/**
 * Implements hook_css_alter().
 */
function radix_css_alter(&$css) {
  // Unset some panopoly css.
  $panopoly_admin_path = drupal_get_path('module', 'panopoly_admin');
  if (isset($css[$panopoly_admin_path . '/panopoly-admin.css'])) {
    unset($css[$panopoly_admin_path . '/panopoly-admin.css']);
  }

  // Unset some core css.
  unset($css['modules/system/system.menus.css']);
}

/**
 * Implements template_preprocess_page().
 */
function radix_preprocess_page(&$variables) {
  global $base_url;

  // Add Bootstrap JS.
  $base = parse_url($base_url);
  drupal_add_js($base['scheme'] . '://netdna.bootstrapcdn.com/twitter-bootstrap/2.3.1/js/bootstrap.min.js', 'external');

  // Add CSS for Font Awesome
  // drupal_add_css('//netdna.bootstrapcdn.com/font-awesome/3.2.1/css/font-awesome.min.css', 'external');

  // Determine if the page is rendered using panels.
  $variables['is_panel'] = FALSE;
  if (module_exists('page_manager') && count(page_manager_get_current_page())) {
    $variables['is_panel'] = TRUE;
  }

  // Make sure tabs is empty.
  if (empty($variables['tabs']['#primary']) && empty($variables['tabs']['#secondary'])) {
    $variables['tabs'] = '';
  }

  // Add search_form to theme.
  $variables['search_form'] = '';
  if (module_exists('search') && user_access('search content')) {
    $search_box_form = drupal_get_form('search_form');
    $search_box_form['basic']['keys']['#title'] = '';
    $search_box_form['basic']['keys']['#attributes'] = array('placeholder' => 'Search');
    $search_box_form['basic']['keys']['#attributes']['class'][] = 'search-query';
    $search_box_form['basic']['submit']['#value'] = t('Search');
    $search_box_form['#attributes']['class'][] = 'navbar-form';
    $search_box_form['#attributes']['class'][] = 'pull-right';
    $search_box = drupal_render($search_box_form);
    $variables['search_form'] = (user_access('search content')) ? $search_box : NULL;
  }

  // Format and add main menu to theme.
  $variables['main_menu'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
  $variables['main_menu']['#theme_wrappers'] = array('menu_tree__primary');

  // Add a copyright message.
  $variables['copyright'] = t('Drupal is a registered trademark of Dries Buytaert.');

  // Display a message if Sass has not been compiled.
  $theme_path = drupal_get_path('theme',$GLOBALS['theme']);
  $stylesheet_path = $theme_path . '/assets/stylesheets/screen.css';
  if (_radix_current_theme() == 'radix') {
    $stylesheet_path = $theme_path . '/assets/stylesheets/radix-style.css';
  }
  if (!file_exists($stylesheet_path)) {
    drupal_set_message(t('It looks like %path has not been created yet. Run <code>@command</code> in your theme directory to create it.', array(
      '%path' => $stylesheet_path,
      '@command' => 'compass watch',
    )), 'error');
  }
}
