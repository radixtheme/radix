/**
 * @file
 * JS for Radix.
 */
(function ($, Drupal, window, document, undefined) {
  $(document).ready(function() {
    // Show tab if hash is provided via url.
    if (hash = window.location.hash) {
      if ($('[href="' + hash + '"]').length) {
        $('[href="' + hash + '"]').tab('show');
      }
    }
  });
})(jQuery, Drupal, this, this.document);
