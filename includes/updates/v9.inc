<?php

/**
 * @file
 * Contains varbase_editor_update_9###(s) hook updates.
 */

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
  // after all used modules. The Module Installer Factory ships with Varbase
  // Core on a full Varbase site; guard the call so this update is a no-op when
  // Varbase Editor is used standalone.
  $module_installer_factory = 'Vardot\\Installer\\ModuleInstallerFactory';
  if (class_exists($module_installer_factory)) {
    call_user_func([$module_installer_factory, 'setModuleWeightAfterInstallation'], 'varbase_editor');
  }
}

/**
 * Issue #3442854: Add CKEditor 5 Paste Filter module to Varbase Editor.
 */
function varbase_editor_update_90004() {

}
