<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class="<?php print $classes; ?>">
    <nav class="navbar navbar-default navbar-static-top" role="navigation">
      <div class="container">
        <div class="navbar-header">
          <?php if (!empty($logo)): ?>
            <a href="<?php print $front_page; ?>" class="navbar-logo">
              <img src="<?php print $logo; ?>" title="<?php print $site_name; ?>" alt="<?php print $site_name; ?>" />
            </a>
          <?php endif; ?>
          <?php if (!empty($logo)): ?>
            <a href="<?php print $front_page; ?>" class="navbar-brand">
              <?php print $site_name; ?>
            </a>
          <?php endif; ?>
        </div> <!-- /.navbar-header -->

        <div class="navbar-right">
          <?php if (!empty($steps)): ?>
            <p class="steps navbar-text"><?php print $steps; ?></p>
          <?php endif; ?>
        </div> <!-- /.navbar-right -->
      </div> <!-- /.container -->
    </nav>

    <main id="main" class="main container">
      <div class="row">
        <?php if (!empty($sidebar_first)): ?>
          <div class="col-md-3 sidebar hidden-sm hidden-xs">
            <?php print $sidebar_first; ?>
          </div>
        <?php endif ?>
        <div class="col-md-9">
          <?php if (!empty($title)): ?>
            <h1 class="page-header"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print $content; ?>
        </div>
      </div>
    </main> <!-- /#main -->
  </body>
</html>