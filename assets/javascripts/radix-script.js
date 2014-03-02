/**
 * @file
 * JS for Radix.
 */
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.RadixTooltips = {
    attach: function(context, settings) {
      $('[data-toggle="tooltip"]', context).tooltip();
    }
  };
  
})(jQuery, Drupal, this, this.document);
