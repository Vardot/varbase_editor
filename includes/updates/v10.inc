<?php

/**
 * @file
 * Contains varbase_editor_update_10###(s) hook updates.
 */

/**
 * Issue #3405819: Add the Anchor Link ~3 module.
 *
 * Configure the CKEditor 5 Rich Editor text format to use it
 */
function varbase_editor_update_100001() {
  if (!\Drupal::moduleHandler()->moduleExists('anchor_link')) {
    \Drupal::service('module_installer')->install(['anchor_link'], FALSE);

    $full_html_config = \Drupal::service('config.factory')->getEditable('editor.editor.full_html');
    if (isset($full_html_config)) {
      $full_html_data = $full_html_config->get();

      if (isset($full_html_data['settings'])
        && isset($full_html_data['settings']['toolbar'])
        && isset($full_html_data['settings']['toolbar']['items'])
        && !in_array('anchor', $full_html_data['settings']['toolbar']['items'])) {

        $final_toolbar_items = [];
        foreach ($full_html_data['settings']['toolbar']['items'] as $toolbar_item) {
          $final_toolbar_items[] = $toolbar_item;
          // Add the "anchor" command button after the "link" command button.
          if ($toolbar_item == 'link') {
            $final_toolbar_items[] = 'anchor';
          }
        }

        $full_html_data['settings']['toolbar']['items'] = $final_toolbar_items;

        $full_html_config->setData($full_html_data)->save(TRUE);

      }
    }
  }
}
