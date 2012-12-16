<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 */
?>
<header id="header" class="header" role="header">
  <div class="container">
    <div class="row">
      <div class="span12">
        <div id="navigation" class="navbar">
          <div class="navbar-inner">
            <div class="container clearfix">
              <?php if ($logo): ?>
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo" class="pull-left brand">
                  <?php print $site_name; ?>
                </a>
              <?php endif; ?>

              <?php if ($main_menu): ?>
                <nav id="main-menu" class="main-menu pull-left" role="navigation">
                  <?php print render($main_menu); ?>
                </nav> <!-- /#main-menu -->
              <?php endif; ?>

              <?php if ($search_form): ?>
                <?php print $search_form; ?>
              <?php endif; ?>
          </div>
        </div> <!-- /#navigation -->
      </div>
    </div>
  </div>
</header>

<div id="main-wrapper">
  <div id="main" class="container">
    <div class="row">
      <?php if ($breadcrumb): ?>
        <div id="breadcrumb" class="span12 inner visible-desktop">
          <?php print $breadcrumb; ?>
        </div>
      <?php endif; ?>
    </div>
    <?php if ($messages): ?>
      <div id="messages">
        <?php print $messages; ?>
      </div>
    <?php endif; ?>
    <div id="content">
      <div class="row">
        <div class="span12 inner">
          <a id="main-content"></a>
          <?php print render($title_prefix); ?>
          <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
          <?php print render($page['help']); ?>
          <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
          <?php print render($page['content']); ?>
        </div>
      </div>
    </div>
  </div>
</div>

<footer id="footer" class="footer" role="footer">
  <div class="container">
    <div class="row">
      <div class="span12">
        <div class="inner">
          <?php print render($footer_menu); ?>
        </div>
      </div>
    </div>
  </div>
</footer>