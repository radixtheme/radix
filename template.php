<?php

/**
 * Implements template_preprocess_page().
 */
function radix_preprocess_page(&$variables) {
}

/**
 * Implements template_preprocess_panels_pane().
 */
function radix_preprocess_panels_pane(&$variables) {
  dpm($variables);
}