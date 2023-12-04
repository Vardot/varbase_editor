<?php

/**
 * @file
 * Contains List of all varbase_editor helpers.
 *
 * Add custom needed helper functions.
 */

/**
 * Implements hook_requirements().
 */
function varbase_editor_requirements($phase) {

  $requirements = [];

  // Check requirements for the CKEditor 5 Anchor Drupal library.
  $ckeditor5_anchor_drupal_library_path = DRUPAL_ROOT . '/libraries/ckeditor5-anchor-drupal/build/anchor-drupal.js';

  // Is the library found in the root libraries path.
  $ckeditor5_anchor_drupal_library_found = file_exists($ckeditor5_anchor_drupal_library_path);

  // If library is not found, then look in the current profile libraries path.
  if (!$ckeditor5_anchor_drupal_library_found) {
    $profile_path = \Drupal::service('extension.list.profile')->getPath(\Drupal::installProfile());
    $profile_path .= '/libraries/ckeditor5-anchor-drupal/build/anchor-drupal.js';
    // Is the library found in the current profile libraries path.
    $ckeditor5_anchor_drupal_library_found = file_exists($profile_path);
  }

  if (!$ckeditor5_anchor_drupal_library_found) {
    $requirements['ckeditor5_anchor_drupal_library'] = [
      'title' => t('CKEditor5 Anchor Drupal library missing'),
      'description' => t('Varbase Editor requires the CKEditor5 Anchor Drupal library.
        Download it (https://github.com/northernco/ckeditor5-anchor-drupal) and place it in the
        libraries folder (/libraries).
        Use the asset-packagist.org method:
        Make sure to change repositories for Drupal and assets:

        ```
        "repositories": {
          "drupal": {
            "type": "composer",
            "url": "https://packages.drupal.org/8"
          },
          "assets": {
            "type": "composer",
            "url": "https://asset-packagist.org"
          }
        },
        ```

        Add the following in the root composer.json for the project

        ```
        "installer-paths": {
          "docroot/libraries/ckeditor5-anchor-drupal": ["npm-asset/northernco--ckeditor5-anchor-drupal"],
          "docroot/libraries/{$name}": [
            "type:drupal-library",
            "type:bower-asset",
            "type:npm-asset"
          ]
        ```

        And

        ```
        "installer-types": [
          "bower-asset",
          "npm-asset"
        ],
        "drupal-libraries": {
          "library-directory": "docroot/libraries",
          "libraries": [
            {"name": "ckeditor5-anchor-drupal", "package": "npm-asset/northernco--ckeditor5-anchor-drupal"}
          ]
        },
        ```
        No need to add anything else with Varbase Profile

        If the project is a Standard Drupal profile is using Varbase Editor, you need to add the following too:
        `"npm-asset/northernco--ckeditor5-anchor-drupal": "^0.4.0"`
        '),
      'severity' => REQUIREMENT_ERROR,
    ];
  }

  // Check requirements for the ACE Editor library.
  $ace_editor_library_path = DRUPAL_ROOT . '/libraries/ace/src/ace.js';

  // Is the library found in the root libraries path.
  $ace_editor_library_found = file_exists($ace_editor_library_path);

  // If library is not found, then look in the current profile libraries path.
  if (!$ace_editor_library_found) {
    $profile_path = \Drupal::service('extension.list.profile')->getPath(\Drupal::installProfile());
    $profile_path .= '/libraries/ace/src/ace.js';
    // Is the library found in the current profile libraries path.
    $ace_editor_library_found = file_exists($profile_path);
  }

  if (!$ace_editor_library_found) {
    $requirements['ace_editor_library'] = [
      'title' => t('ACE Editor library missing'),
      'description' => t('Varbase Editor requires the Ace Editor library.
        Download it (https://github.com/ajaxorg/ace-builds) and place it in the
        libraries folder (/libraries).
        Use the asset-packagist.org method:
        Make sure to change repositories for Drupal and assets:

        ```
        "repositories": {
          "drupal": {
            "type": "composer",
            "url": "https://packages.drupal.org/8"
          },
          "assets": {
            "type": "composer",
            "url": "https://asset-packagist.org"
          }
        },
        ```

        Add the following in the root composer.json for the project

        ```
        "installer-paths": {
          "docroot/libraries/ace": ["npm-asset/ace-builds"],
          "docroot/libraries/{$name}": [
            "type:drupal-library",
            "type:bower-asset",
            "type:npm-asset"
          ]
        }

        ```

        And

        ```
        "installer-types": [
          "bower-asset",
          "npm-asset"
        ],
        "drupal-libraries": {
          "library-directory": "docroot/libraries",
          "libraries": [
            {"name": "ace", "package": "npm-asset/ace-builds"},
          ]
        },
        ```
        No need to add anything else with Varbase Profile

        If the project is a Standard Drupal profile is using Varbase Editor, you need to add the following too:
        `"npm-asset/ace-builds": "~1",`
        '),
      'severity' => REQUIREMENT_ERROR,
    ];
  }

  // Check requirements for the Blazy library.
  $blazy_library_path = DRUPAL_ROOT . '/libraries/blazy/blazy.js';

  // Is the library found in the root libraries path.
  $blazy_library_found = file_exists($blazy_library_path);

  // If library is not found, then look in the current profile libraries path.
  if (!$blazy_library_found) {
    $profile_path = \Drupal::service('extension.list.profile')->getPath(\Drupal::installProfile());
    $profile_path .= '/libraries/blazy/blazy.js';
    // Is the library found in the current profile libraries path.
    $blazy_library_found = file_exists($profile_path);
  }

  if (!$blazy_library_found) {
    $requirements['blazy_library'] = [
      'title' => t('Blazy library missing'),
      'description' => t('Varbase Editor requires the Blazy library.
        Download it (https://github.com/dinbror/blazy) and place it in the
        libraries folder (/libraries).
        Use the asset-packagist.org method:
        Make sure to change repositories for Drupal and assets:

        ```
        "repositories": {
          "drupal": {
            "type": "composer",
            "url": "https://packages.drupal.org/8"
          },
          "assets": {
            "type": "composer",
            "url": "https://asset-packagist.org"
          }
        },
        ```

        Add the following in the root composer.json for the project

        ```
        "installer-paths": {
          "docroot/libraries/blazy": ["npm-asset/blazy"],
          "docroot/libraries/{$name}": [
            "type:drupal-library",
            "type:bower-asset",
            "type:npm-asset"
          ]
        }

        ```

        And

        ```
        "installer-types": [
          "bower-asset",
          "npm-asset"
        ],
        "drupal-libraries": {
          "library-directory": "docroot/libraries",
          "libraries": [
            {"name": "blazy", "package": "npm-asset/blazy"},
          ]
        },
        ```
        No need to add anything else with Varbase Profile

        If the project is a Standard Drupal profile is using Varbase Editor, you need to add the following too:
        `"npm-asset/blazy": "~1",`
        '),
      'severity' => REQUIREMENT_ERROR,
    ];
  }

  // Check requirements for the Slick library.
  $slick_library_path = DRUPAL_ROOT . '/libraries/slick/slick/slick.js';

  // Is the library found in the root libraries path.
  $slick_library_found = file_exists($slick_library_path);

  // If library is not found, then look in the current profile libraries path.
  if (!$slick_library_found) {
    $profile_path = \Drupal::service('extension.list.profile')->getPath(\Drupal::installProfile());
    $profile_path .= '/libraries/slick/slick/slick.js';
    // Is the library found in the current profile libraries path.
    $slick_library_found = file_exists($profile_path);
  }

  if (!$slick_library_found) {
    $requirements['slick_library'] = [
      'title' => t('slick library missing'),
      'description' => t('Varbase Editor requires the Slick library.
        Download it (https://github.com/kenwheeler/slick) and place it in the
        libraries folder (/libraries).
        Use the asset-packagist.org method:
        Make sure to change repositories for Drupal and assets:

        ```
        "repositories": {
          "drupal": {
            "type": "composer",
            "url": "https://packages.drupal.org/8"
          },
          "assets": {
            "type": "composer",
            "url": "https://asset-packagist.org"
          }
        },
        ```

        Add the following in the root composer.json for the project

        ```
        "installer-paths": {
          "docroot/libraries/slick": ["npm-asset/slick-carousel"],
          "docroot/libraries/{$name}": [
            "type:drupal-library",
            "type:bower-asset",
            "type:npm-asset"
          ]
        }

        ```

        And

        ```
        "installer-types": [
          "bower-asset",
          "npm-asset"
        ],
        "drupal-libraries": {
          "library-directory": "docroot/libraries",
          "libraries": [
            {"name": "slick", "package": "npm-asset/slick-carousel"},
          ]
        },
        ```
        No need to add anything else with Varbase Profile

        If the project is a Standard Drupal profile is using Varbase Editor, you need to add the following too:
        `"npm-asset/slick-carousel": "~1",`
        '),
      'severity' => REQUIREMENT_ERROR,
    ];
  }

  return $requirements;
}
