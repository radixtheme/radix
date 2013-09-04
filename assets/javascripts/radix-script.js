/**
 * @file
 * JS for Radix.
 */
(function ($) {
  $(document).ready(function() {
    // menu dropdown
    $('.navbar ul.nav li.dropdown').mouseenter(function() {
      $(this).addClass('open');
    });
    $('.navbar ul.nav li.dropdown').mouseleave(function() {
      $(this).removeClass('open');
    });

    // Tooltip.
    $('[data-toggle="tooltip"]').tooltip();
  });
})(jQuery);
