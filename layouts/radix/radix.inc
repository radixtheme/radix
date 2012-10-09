<?php

// Plugin definition
$plugin = array(
  'title' => t('Radix'),
  'category' => t('Radix'),
  'icon' => 'radix-desktop.png',
  'sets' => array(
    'desktop' => array(
      'title' => t('Desktop'),                       
      'icon' => 'radix-desktop.png'
    ),
  ),
  'theme' => 'panels_dmltwocolfront',
  'css' => 'dmltwocolfront.css',
  'regions' => array(
    'left' => t('Left'),
    'right' => t('Right')
  ),
  'description' => t('This is description')
);
