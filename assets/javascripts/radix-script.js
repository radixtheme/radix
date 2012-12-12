(function ($) {
  $(document).ready(function() {
    // menu dropdown
    $('ul.menu li.expanded').mouseenter(function() {
      $(this).addClass('open');
    });
    $('ul.menu li.expanded').mouseleave(function() {
      $(this).removeClass('open');
    });
  });
})(jQuery);
