<?php
/**
 * @file
 * Theme functions
 */

require_once dirname(__FILE__) . '/includes/theme.inc';
require_once dirname(__FILE__) . '/includes/structure.inc';
require_once dirname(__FILE__) . '/includes/field.inc';
require_once dirname(__FILE__) . '/includes/comment.inc';
require_once dirname(__FILE__) . '/includes/form.inc';
require_once dirname(__FILE__) . '/includes/menu.inc';
require_once dirname(__FILE__) . '/includes/node.inc';
require_once dirname(__FILE__) . '/includes/panel.inc';
require_once dirname(__FILE__) . '/includes/block.inc';
require_once dirname(__FILE__) . '/includes/user.inc';
require_once dirname(__FILE__) . '/includes/view.inc';

/**
 * Implements template_preprocess_page().
 */
function {{machine_name}}_preprocess_page(&$variables) {
  // Add copyright to theme.
  if ($copyright = theme_get_setting('copyright')) {
    $variables['copyright'] = check_markup($copyright['value'], $copyright['format']);
  }
}
