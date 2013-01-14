<?php

/**
 * Implementation of template_preprocess_html()
 */
function radix_preprocess_html(&$variables) {
 
  // add meta for Bootstrap Responsive
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
 * Implements hook_js_alter().
 */
function radix_js_alter(&$js) {
  //$js['misc/jquery.js']['data'] = 'http://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js';
}

/**
 * Implements hook_css_alter().
 */
function radix_css_alter(&$css) {
  if (isset($css['sites/all/modules/panopoly/panopoly_admin/panopoly-admin.css'])) {
    unset($css['sites/all/modules/panopoly/panopoly_admin/panopoly-admin.css']);
  }
}

/**
 * Implements template_preprocess_page().
 */
function radix_preprocess_page(&$variables) {

  // determine if the page is rendered using panels
  $variables['is_panel'] = FALSE;
  if (sizeof(page_manager_get_current_page())) {
    $variables['is_panel'] = TRUE;
  }

  // Add search_form to theme
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

  // Format and add main menu to theme
  $main_menu_tree = menu_tree_all_data('main-menu');
  $variables['main_menu'] = menu_tree_output($main_menu_tree);

  // Format and add footer menu to theme
  $footer_menu_tree = menu_tree_all_data('menu-footer-menu');
  $variables['footer_menu'] = menu_tree_output($footer_menu_tree);
}

/**
 * Implements template_preprocess_navbar().
 */
function radix_preprocess_navbar(&$variables) {
  $navbar = $variables['navbar'];
  $variables['navbar'] = $navbar;
}

/**
 * Implements theme_table().
 */
function radix_table($variables) {
  // add default classes to table elements
  $variables['attributes']['class'] = (isset($variables['attributes']['class'])) ? $variables['attributes']['class'] : array();
  $variables['attributes']['class'] = array_merge($variables['attributes']['class'], array('table', 'table-striped', 'table-bordered'));
  
  $header = $variables['header'];
  $rows = $variables['rows'];
  $attributes = $variables['attributes'];
  $caption = $variables['caption'];
  $colgroups = $variables['colgroups'];
  $sticky = $variables['sticky'];
  $empty = $variables['empty'];

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled';
  }

  $output = '<table' . drupal_attributes($attributes) . ">\n";

  if (isset($caption)) {
    $output .= '<caption>' . $caption . "</caption>\n";
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $number => $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }
        $output .= " </colgroup>\n";
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . " />\n";
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;
    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }
    $rows[] = array(array(
        'data' => $empty,
        'colspan' => $header_count,
        'class' => array('empty', 'message'),
      ));
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? ' <thead><tr>' : ' <tr>');
    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }
    // Using ternary operator to close the tags based on whether or not there are rows
    $output .= (count($rows) ? " </tr></thead>\n" : "</tr>\n");
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= "<tbody>\n";
    $flip = array(
      'even' => 'odd',
      'odd' => 'even',
    );
    $class = 'even';
    foreach ($rows as $number => $row) {
      $attributes = array();

      // Check if we're dealing with a simple or complex row
      if (isset($row['data'])) {
        foreach ($row as $key => $value) {
          if ($key == 'data') {
            $cells = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cells = $row;
      }
      if (count($cells)) {
        // Add odd/even class
        if (empty($row['no_striping'])) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        // Build row
        $output .= ' <tr' . drupal_attributes($attributes) . '>';
        $i = 0;
        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);
          $output .= _theme_table_cell($cell);
        }
        $output .= " </tr>\n";
      }
    }
    $output .= "</tbody>\n";
  }

  $output .= "</table>\n";
  return $output;
}

/**
 * Returns HTML for a button form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #button_type, #name, #value.
 *
 * @ingroup themeable
 */
function radix_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  $element['#attributes']['class'][] = 'btn';
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // add a btn-primary class if submit button
  if ($element['#parents'][0] == 'submit') {
    $element['#attributes']['class'][] = 'btn-primary'; 
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Implements theme_menu_link().
 */
function radix_link($variables) {
  $icons = '';
  if (isset($variables['options']['attributes']['class']) && is_array($variables['options']['attributes']['class'])) {
    $css_classes = $variables['options']['attributes']['class'];
    if ($icon_classes = preg_grep('/^icon\-.*/', $css_classes)) {
      // render an icon for each class
      foreach ($icon_classes as $icon_class) {
        $icons .= '<i class="' . $icon_class . '"></i>';
      }
      // unset icon classes for attributes to prevent double rendering
      $variables['options']['attributes']['class'] = array_diff($css_classes, $icon_classes);
    }
  }
  return '<a href="' . check_plain(url($variables['path'], $variables['options'])) . '"' . drupal_attributes($variables['options']['attributes']) . '>' . $icons . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a>';
}