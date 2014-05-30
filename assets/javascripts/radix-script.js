/**
 * @file
 * JS for Radix.
 */
(function ($, Drupal, window, document, undefined) {
  $(document).ready(function() {
    // Show dropdown on hover.
    $('.dropdown').mouseenter(function() {
      $(this).addClass('open');
    });
    $('.dropdown').mouseleave(function() {
      $(this).removeClass('open');
    });
  });
})(jQuery, Drupal, this, this.document);
