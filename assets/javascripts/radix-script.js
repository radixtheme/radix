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

    // Allow main menu dropdown-toggle to be clickable.
    $('#main-menu .dropdown > a.dropdown-toggle').click(function(e) {
      e.preventDefault();
      window.location.href = $(this).attr('href');
    });
  });
})(jQuery, Drupal, this, this.document);
