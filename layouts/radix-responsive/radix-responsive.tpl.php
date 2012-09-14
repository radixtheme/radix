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

<div class="panel-display container radix-responsive-panel-layout clearfix <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <?php if ($content['top']): ?>
    <div class="top panel-panel">
      <div class="span12 panel-panel-inner">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <div class="center-wrapper">
    <div class="span3 panel-panel left sidebar">
      <div class="panel-panel-inner">
        <?php print $content['left']; ?>
      </div>
    </div>
    <div class="span7 panel-panel center">
      <div class="panel-panel-inner">
        <?php print $content['center']; ?>
      </div>
    </div>
    <div class="span2 panel-panel right sidebar">
      <div class="panel-panel-inner">
        <?php print $content['right']; ?>
      </div>
    </div>
  </div>

  <?php if ($content['bottom']): ?>
    <div class="bottom panel-panel">
      <div class="span12 panel-panel-inner">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif; ?>
  
</div><!-- /.panel-display -->
