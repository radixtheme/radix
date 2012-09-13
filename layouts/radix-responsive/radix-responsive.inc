<?php

// Plugin definition
$plugin = array(
  'title' => t('Radix Responsive'),
  'category' => t('Radix'),
  'sets' => array(
    'desktop' => array(
      'title' => t('Desktop'),                       
      'icon' => 'radix-responsive-desktop.png'
    ),
    'tablet' => array(
      'title' => t('Tablet'),                       
      'icon' => 'radix-responsive-tablet.png'
    ),
    'mobile' => array(
      'title' => t('Mobile'),                       
      'icon' => 'radix-responsive-mobile.png'
    ),
  ),
  'theme' => 'radix_responsive',
  'regions' => array(
    'header' => t('Header'),
    'left' => t('Left'),
    'content' => t('Content'),
    'right' => t('Right'),
    'footer' => t('Footer'),
  ),
);
