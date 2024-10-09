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

/**
 * Merges two allowed HTML strings used in CKEditor 5's filter settings.
 *
 * This function combines two strings of allowed HTML tags and attributes, ensuring:
 * - Duplicate tags are eliminated.
 * - Tags with attributes are merged if they appear in both strings with different attributes.
 * - If a tag appears without attributes but exists with attributes, the version with attributes is preferred.
 *
 * This is useful for configuring CKEditor's "Limit allowed HTML tags and correct faulty HTML" filter.
 * Supports custom XML tags such as `drupal-*`.
 *
 * @param string $allowed_html1
 *   The first string of allowed HTML tags.
 * @param string $allowed_html2
 *   The second string of allowed HTML tags.
 *
 * @return string
 *   A string containing the merged and unique allowed HTML tags, where attributes are combined when both versions have them.
 */
function varbase_editor__merge_allowed_html(string $allowed_html1, string $allowed_html2): string {
  // Combine the two strings.
  $merged_string = $allowed_html1 . ' ' . $allowed_html2;

  // Split the string into individual tags, allowing custom XML tags like 'drupal-*'.
  preg_match_all('/<[\w-]+(\s+[^>]+)?>/', $merged_string, $matches);

  $unique_tags = [];

  foreach ($matches[0] as $tag) {
    // Extract the tag name and its attributes.
    preg_match('/<([\w-]+)(\s+[^>]*)?>/', $tag, $tag_parts);

    if (isset($tag_parts[1])) {
      // The tag name (e.g., "div", "span", "drupal-media").
      $tag_name = $tag_parts[1];
      $attributes = isset($tag_parts[2]) ? trim($tag_parts[2]) : '';

      // If the tag is already seen and has attributes, merge the attributes.
      if (isset($unique_tags[$tag_name])) {
        // Extract existing attributes.
        preg_match('/<[^>]+\s([^>]+)>/', $unique_tags[$tag_name], $existing_parts);
        $existing_attributes = isset($existing_parts[1]) ? $existing_parts[1] : '';

        // Combine unique attributes.
        if ($attributes) {
          $combined_attributes = varbase_editor__merge_attributes($existing_attributes, $attributes);
          $unique_tags[$tag_name] = "<{$tag_name} {$combined_attributes}>";
        }
      }
      else {
        // Add the tag as a unique entry.
        $unique_tags[$tag_name] = $tag;
      }
    }
  }

  // Join the unique tags back into a single string.
  $final_string = implode(' ', $unique_tags);

  // Return the merged string with unique tags and merged attributes.
  return $final_string;
}

/**
 * Helper function to merge two sets of HTML tag attributes.
 *
 * This function combines attributes from two versions of the same tag, ensuring that:
 * - Duplicate attributes are removed.
 * - Class attributes are merged, while other attributes are replaced by the more recent version.
 *
 * @param string $attributes1
 *   The first set of attributes.
 * @param string $attributes2
 *   The second set of attributes.
 *
 * @return string
 *   The combined attributes, with duplicate and conflicting attributes resolved.
 */
function varbase_editor__merge_attributes(string $attributes1, string $attributes2): string {
  // Parse attributes into key-value pairs.
  $attr1 = varbase_editor__parse_attributes($attributes1);
  $attr2 = varbase_editor__parse_attributes($attributes2);

  // Merge attributes, ensuring unique values for class attributes.
  foreach ($attr2 as $key => $value) {
    if ($key === 'class') {
      // Merge classes uniquely.
      $merged_classes = array_unique(array_merge(explode(' ', $attr1['class'] ?? ''), explode(' ', $value)));
      $attr1['class'] = trim(implode(' ', $merged_classes));
    }
    else {
      // Override or add new attributes.
      $attr1[$key] = $value;
    }
  }

  // Convert attributes back to string format.
  $merged_attributes = [];
  foreach ($attr1 as $key => $value) {
    $merged_attributes[] = "{$key}=\"{$value}\"";
  }

  return implode(' ', $merged_attributes);
}

/**
 * Helper function to parse HTML attributes into key-value pairs.
 *
 * @param string $attributes
 *   The string of HTML attributes.
 *
 * @return array
 *   An associative array of attribute keys and their corresponding values.
 */
function varbase_editor__parse_attributes(string $attributes): array {
  $result = [];
  preg_match_all('/(\w+)=("[^"]*"|\'[^\']*\')/', $attributes, $matches, PREG_SET_ORDER);

  foreach ($matches as $match) {
    $key = $match[1];
    // Remove quotes around attribute values.
    $value = trim($match[2], '"\'');
    $result[$key] = $value;
  }

  return $result;
}
