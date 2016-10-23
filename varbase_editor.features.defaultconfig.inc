<?php
/**
 * @file
 * varbase_editor.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function varbase_editor_defaultconfig_features() {
  return array(
    'varbase_editor' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function varbase_editor_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'filter_fallback_format';
  $strongarm->value = 'plain_text';
  $export['filter_fallback_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'media_icon_base_directory';
  $strongarm->value = 'public://media-icons';
  $export['media_icon_base_directory'] = $strongarm;

  return $export;
}
