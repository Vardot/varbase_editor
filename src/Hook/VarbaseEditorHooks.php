<?php

declare(strict_types=1);

namespace Drupal\varbase_editor\Hook;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Hook\Attribute\Hook;
use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\varbase_editor\Plugin\Filter\VarbaseFilterResizeMedia;

/**
 * Hook implementations for the Varbase Editor module.
 */
class VarbaseEditorHooks {

  use StringTranslationTrait;

  /**
   * Constructs a VarbaseEditorHooks object.
   *
   * @param \Drupal\Core\Extension\ModuleHandlerInterface $moduleHandler
   *   The module handler.
   */
  public function __construct(
    protected ModuleHandlerInterface $moduleHandler,
  ) {}

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

    // Check if the CKEditor Media Resize module is enabled.
    if ($this->moduleHandler->moduleExists('ckeditor_media_resize')) {
      if (isset($settings['editor']['formats']['full_html']['editorSettings']['config']['drupalMedia'])) {
        // Change the 'resizeUnit' from 'px' to '%'.
        $settings['editor']['formats']['full_html']['editorSettings']['config']['drupalMedia']['resizeUnit'] = '%';

        // Check if the settings for the 'full_html' format are available.
        if (isset($settings['editor']['formats']['full_html']['editorSettings']['config']['drupalMedia']['resizeOptions'])) {
          // Add additional resize options to the 'resizeOptions' array.
          $settings['editor']['formats']['full_html']['editorSettings']['config']['drupalMedia']['resizeOptions'][] = [
            'name' => 'resizeMediaImage:100',
            'value' => 100,
            'label' => $this->t('Large'),
          ];
          $settings['editor']['formats']['full_html']['editorSettings']['config']['drupalMedia']['resizeOptions'][] = [
            'name' => 'resizeMediaImage:50',
            'value' => 50,
            'label' => $this->t('Medium'),
          ];
          $settings['editor']['formats']['full_html']['editorSettings']['config']['drupalMedia']['resizeOptions'][] = [
            'name' => 'resizeMediaImage:25',
            'value' => 25,
            'label' => $this->t('Small'),
          ];
        }
      }
    }
  }

  /**
   * Implements hook_library_info_alter().
   */
  #[Hook('library_info_alter')]
  public function libraryInfoAlter(array &$libraries, $module): void {
    // Varbase Editor custom style fixes for CKEditor5.
    if ($module === 'ckeditor5' && isset($libraries['internal.drupal.ckeditor5.stylesheets'])) {
      $libraries['internal.drupal.ckeditor5.stylesheets']['dependencies'][] = 'varbase_editor/ckeditor5';
    }

    // Add 'varbase_editor/ckeditor5-media-resize' as a dependency
    // for ckeditor_media_resize library.
    if ($module === 'ckeditor_media_resize' && isset($libraries['editor'])) {
      $libraries['editor']['dependencies'][] = 'varbase_editor/ckeditor5-media-resize';
    }

    if ($module === 'layout_builder' && isset($libraries['drupal.layout_builder'])) {
      $libraries['drupal.layout_builder']['dependencies'][] = 'varbase_editor/ckeditor5';
      $libraries['drupal.layout_builder']['dependencies'][] = 'varbase_editor/ckeditor5-media-resize';
    }
  }

  /**
   * Implements hook_filter_info_alter().
   */
  #[Hook('filter_info_alter')]
  public function filterInfoAlter(array &$info): void {
    if (isset($info['filter_resize_media'])) {
      // Replace the class for the 'filter_resize_media' filter
      // with 'VarbaseFilterResizeMedia'.
      $info['filter_resize_media']['class'] = VarbaseFilterResizeMedia::class;
    }
  }

}
