<?php
/**
 * @file
 * Template for Radix Responsive.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display container clearfix <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="header panel-panel">
    <div class="span12 panel-panel-inner">
      <?php print $content['header']; ?>
    </div>
  </div>
  
  <div class="center-wrapper">
    <div class="span3 panel-panel left sidebar">
      <div class="panel-panel-inner">
        <?php print $content['left']; ?>
      </div>
    </div>
    <div class="span7 panel-panel content">
      <div class="panel-panel-inner">
        <?php print $content['content']; ?>
      </div>
    </div>
    <div class="span2 panel-panel right sidebar">
      <div class="panel-panel-inner">
        <?php print $content['right']; ?>
      </div>
    </div>
  </div>

  <div class="footer panel-panel">
    <div class="span12 panel-panel-inner">
      <?php print $content['footer']; ?>
    </div>
  </div>
  
</div><!-- /.panel-display -->
