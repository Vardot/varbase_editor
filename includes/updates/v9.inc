<?php

/**
 * @file
 * Contains varbase_editor_update_9###(s) hook updates.
 */

use Vardot\Installer\ModuleInstallerFactory;

/**
 * Issue #3264253: Disable Blazy per individual Video iframe.
 *
 * For the Rich editor and Simple editor text formats.
 */
function varbase_editor_update_90001() {

}

/**
 * Issue #3264445: Add and enable CKEditor Paste Filter module.
 */
function varbase_editor_update_90002() {

  // Enable CKEditor Paste Filter module if it was not enabled yet.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor_paste_filter')) {
    \Drupal::service('module_installer')->install(['ckeditor_paste_filter'], FALSE);
  }

  try {
    // Flag the update checklist item as done.
    // Only if Varbase Update Helper, and Varbase Core was enabled.
    if (\Drupal::moduleHandler()->moduleExists('varbase_update_helper')
      && \Drupal::moduleHandler()->moduleExists('varbase_core')) {

      /** @var \Drupal\update_helper\Updater $updateHelper */
      $updateHelper = \Drupal::service('update_helper.updater');

      // Execute configuration update definitions with logging of success.
      $updateHelper->executeUpdate('varbase_core', 'varbase_editor_update_90002');

      // Output logged messages to related channel of update execution.
      return $updateHelper->logger()->output();
    }
  }
  catch (Exception $e) {
    // Ignore exception when Varbase Editor is not used with Varbase Core.
  }
}

/**
 * Issue #3272283: Switch to use the Module Installer Factory.
 *
 * In the Varbase Editor module.
 */
function varbase_editor_update_90003() {
  // Set the weight of the module after installation of list of modules.
  // To make sure that any hook or event subscriber worker
  // after all used modules.
  ModuleInstallerFactory::setModuleWeightAfterInstallation('varbase_editor');
}

/**
 * Issue #3442854: Add CKEditor 5 Paste Filter module to Varbase Editor.
 */
function varbase_editor_update_90004() {
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor5_paste_filter')) {

    // Install CKEditor 5 Paste Filter module.
    \Drupal::service('module_installer')->install(['ckeditor5_paste_filter'], FALSE);

    // Update Simple and Rich Editors text formats with default filter configs.
    $editors = [
      'editor.editor.full_html',
      'editor.editor.basic_html',
    ];

    $manager = \Drupal::service('plugin.manager.ckeditor5.plugin');
    $paste_filter = $manager->getPlugin('ckeditor5_paste_filter_pasteFilter', NULL);
    $paste_filter_config = $paste_filter->defaultConfiguration();
    $paste_filter_config['enabled'] = TRUE;

    foreach ($editors as $editor) {
      $editor_config = \Drupal::service('config.factory')->getEditable($editor);
      if ($editor_config) {
        $editor_data = $editor_config->get();
        if (isset($editor_data['settings']['plugins'])) {
          $editor_data['settings']['plugins']['ckeditor5_paste_filter_pasteFilter'] = $paste_filter_config;
        }
        else {
          $editor_data['settings']['plugins'] = [
              'ckeditor5_paste_filter_pasteFilter' => $paste_filter_config,
          ];
        }
        $editor_config->setData($editor_data)->save(TRUE);
      }
    }
  }
}
