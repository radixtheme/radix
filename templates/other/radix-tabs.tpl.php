<?php

/**
 * @file
 * Template file for Radix Tabs.
 */
?>
<?php if (count($tabs)): ?>
  <!-- Nav tabs -->
  <ul class="nav nav-tabs">
    <?php foreach ($tabs as $tab): ?>
      <li><a href="#<?php print $tab['id']; ?>" data-toggle="tab"><?php print $tab['title']; ?></a></li>
    <?php endforeach; ?>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content">
    <?php foreach ($tabs as $tab): ?>
      <div class="tab-pane" id="<?php print $tab['id']; ?>"><?php print $tab['content']; ?></div>
    <?php endforeach; ?>
  </div>
<?php endif; ?>
