<?php

// Plugin definition
$plugin = array(
  'title' => t('Radix Responsive'),
  'category' => t('Radix'),
  'icon' => 'radix-responsive-desktop.png',
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
    'top' => t('Top'),
    'left' => t('Left'),
    'center' => t('Center'),
    'right' => t('Right'),
    'bottom' => t('Bottom'),
  ),
  'css' => 'radix-responsive.css'
);
