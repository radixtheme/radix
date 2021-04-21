<?php

/**
 * @file
 * Contains Drush hooks.
 */

use Drupal\Component\Utility\UrlHelper;

/**
 * Implements hook_drush_command().
 */
function radix_drush_command() {
  $items = [];

  $items['radix'] = [
    'description' => 'Create a Radix subtheme.',
    'arguments' => [
      'name'         => 'The name of your subtheme.',
    ],
    'options' => [
      'machine_name' => 'The machine-readable name of your subtheme. This will be auto-generated from the human-readable name if ommited.',
      'description' => 'The description of your subtheme',
      'destination' => 'The destination of your subtheme. Defaults to "./themes".',
      'kit' => 'The name or url of the starter kit to use. Defaults to "default".',
    ],
    'examples' => [
      'drush radix "My Theme"' => 'Creates a Radix subtheme called "My Theme", using the default options.',
      'drush radix "My Theme" --machine_name=my_theme' => 'Creates a Radix subtheme called "My Theme" with a specific machine name.',
    ],
  ];

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function radix_drush_help($section) {
  switch ($section) {
    case 'drush:radix':
      return dt('This command will create a Radix subtheme. See examples to get started.');

    break;
  }
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_radix($name = NULL, $machine_name = NULL) {

  // If no $name provided, abort.
  if (!$name) {
    drush_print(dt('Theme name missing. See help using drush radix --help.'));
    return;
  }

  // Determine the theme name.
  if (!isset($name)) {
    $name = drush_get_option('name');
  }

  // Determine the machine name.
  if (!isset($machine_name)) {
    $machine_name = drush_get_option('machine_name');
  }
  if (!$machine_name) {
    $machine_name = $name;
  }
  $machine_name = str_replace(' ', '_', strtolower($machine_name));
  $search = [
  // Remove characters not valid in function names.
    '/[^a-z0-9_]/',
  // Functions must begin with an alpha character.
    '/^[^a-z]+/',
  ];
  $machine_name = preg_replace($search, '', $machine_name);

  // Description of subtheme.
  $description = (drush_get_option('description')) ? trim(drush_get_option('description')) : 'A theme based on Radix.';

  // Determine the path to the new subtheme.
  $subtheme_path = 'themes';
  if ($path = drush_get_option('path')) {
    $subtheme_path = drush_trim_path($path);
  }
  $subtheme_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . $subtheme_path . '/' . $machine_name);

  // Determine the kit to use.
  $kit = (drush_get_option('kit')) ? drush_trim_path(drush_get_option('kit')) : 'default';

  // Make a fresh copy of the kit.
  $kit_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'radix') . '/src/kits/' . $kit);

  // Allow kits to be pulled from external urls.
  if (UrlHelper::isValid($kit, TRUE)) {
    $kit_url = $kit;
    $kit_name = 'kit';

    // Get kit name from kit url.
    if (preg_match("/\/radix\-kit\-([a-z0-9\_]*)\//", $kit_url, $matches)) {
      $kit_name = $kit = $matches[1];
    }

    // Switch to a temp directory.
    $current_dir = getcwd();
    chdir(drush_tempdir());

    drush_print(dt('Downloading @kit_name from @kit_url...', [
      '@kit_name' => (!empty($kit_name)) ? $kit_name . ' kit' : $kit_name,
      '@kit_url' => $kit_url,
    ]));
    if ($filepath = drush_download_file($kit_url)) {
      $filename = basename($filepath);

      // Decompress the zip archive.
      $files = drush_tarball_extract($filename, getcwd(), TRUE);

      // Re-index array.
      // This fixes an issue where a .tag.gz tarball returns a non-zero array.
      $files = array_values($files);
      $kit_path = getcwd() . '/' . $files[0];

      // Set working directory back to the previous working directory.
      chdir($current_dir);
    }
  }

  if (!is_dir(dirname($subtheme_path))) {
    drush_die(dt('The directory "!directory" was not found.', ['!directory' => dirname($subtheme_path)]));
  }
  drush_op('drush_copy_dir', $kit_path, $subtheme_path);

  // Alter the contents of the .info file based on the command options.
  $alterations = [
    'RADIX_SUBTHEME_NAME' => $name,
    'RADIX_SUBTHEME_DESCRIPTION' => $description,
    'RADIX_SUBTHEME_MACHINE_NAME' => $machine_name,
    'hidden: true' => '',
  ];

  // Replace all occurrences of '{{machine_name}}' with the machine name of our sub theme.
  $files_to_replace = radix_get_files_to_make_replacements($kit);
  foreach ($files_to_replace as $file_to_replace) {
    drush_op('radix_file_str_replace', $subtheme_path . '/' . $file_to_replace, array_keys($alterations), $alterations);
  }

  // Rename files.
  $files_to_rename = [
    '{{kit}}.info.yml',
    '{{kit}}.libraries.yml',
    '{{kit}}.breakpoints.yml',
    '{{kit}}.theme',
    'config/schema/{{kit}}.schema.yml',
    'src/sass/{{kit}}.style.scss',
    'src/js/{{kit}}.script.js',
  ];
  foreach ($files_to_rename as $file_to_rename_path) {
    $file_original_path = $subtheme_path . '/' . str_replace('{{kit}}', $kit, $file_to_rename_path);
    $file_new_path = $subtheme_path . '/' . str_replace('{{kit}}', $machine_name, $file_to_rename_path);
    drush_op('rename', drush_normalize_path($file_original_path), drush_normalize_path($file_new_path));
  }

  // Notify user of the newly created theme.
  $message = 'Successfully created the Radix subtheme "!name" in "!path" using the "!kit" kit';

  $message = dt($message . '.', [
    '!name' => $name,
    '!path' => $subtheme_path,
    '!kit' => $kit,
  ]);
  drush_print($message);
}

/**
 * Replace strings in a file.
 */
function radix_file_str_replace($file_path, $find, $replace) {
  $file_path = drush_normalize_path($file_path);
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}

/**
 * Returns an array of files to make string replacements.
 */
function radix_get_files_to_make_replacements($kit = 'default') {
  return [
    $kit . '.info.yml',
    $kit . '.libraries.yml',
    $kit . '.theme',
    'package.json',
    'package-lock.json',
    'webpack.mix.js',
    'README.md',
    'templates/content/node.html.twig',
    'config/schema/' . $kit . '.schema.yml',
  ];
}
