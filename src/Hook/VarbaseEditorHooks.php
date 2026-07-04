<?php

declare(strict_types=1);

namespace Drupal\varbase_editor\Hook;

use Drupal\Core\Hook\Attribute\Hook;

/**
 * Hook implementations for the Varbase Editor module.
 */
class VarbaseEditorHooks {

  /**
   * Implements hook_editor_js_settings_alter().
   */
  #[Hook('editor_js_settings_alter')]
  public function editorJsSettingsAlter(array &$settings): void {

    // Remove h1 from Editor formats in the Full HTML (Rich editor) Text format.
    if (isset($settings['editor'])
      && isset($settings['editor']['formats'])
      && isset($settings['editor']['formats']['full_html'])
      && isset($settings['editor']['formats']['full_html']['editorSettings'])
      && isset($settings['editor']['formats']['full_html']['editorSettings']['format_tags'])
      && strpos($settings['editor']['formats']['full_html']['editorSettings']['format_tags'], 'h1;')) {

      $format_tags = str_replace('h1;', '', $settings['editor']['formats']['full_html']['editorSettings']['format_tags']);
      $settings['editor']['formats']['full_html']['editorSettings']['format_tags'] = $format_tags;
    }
  }

}
