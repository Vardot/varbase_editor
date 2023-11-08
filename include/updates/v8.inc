<?php

/**
 * @file
 * Contains varbase_editor_update_8###(s) hook updates.
 */

use Symfony\Component\Yaml\Yaml;

/**
 * WARNING: The "Full HTML" text format was mistakenly referred to by its.
 *
 * Machine name (restricted_html), this is confusing and wrong. Therefore,
 * this filter has been deprecated in favor of better naming to become
 * "HTML code" (code_html).
 *
 * Please make sure to revise your content if it was using the "Full HTML"
 * text format. You can enable it again if you like, or switch to use the
 * new "HTML code" text format.
 */
function varbase_editor_update_8001() {
  // Enable HTML code text format (code_html).
  $code_html_editor_config = \Drupal::service('config.factory')->getEditable('editor.editor.code_html');
  $code_html_editor_config_file = \Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/editor.editor.code_html.yml';
  $code_html_editor_config_content = file_get_contents($code_html_editor_config_file);
  $code_html_editor_config_content_data = (array) Yaml::parse($code_html_editor_config_content);
  $code_html_editor_config->setData($code_html_editor_config_content_data)->save();

  $code_html_format_config = \Drupal::service('config.factory')->getEditable('filter.format.code_html');
  $code_html_format_config_file = \Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/filter.format.code_html.yml';
  $code_html_format_config_content = file_get_contents($code_html_format_config_file);
  $code_html_format_config_content_data = (array) Yaml::parse($code_html_format_config_content);
  $code_html_format_config->setData($code_html_format_config_content_data)->save();

  if (file_exists(\Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/filter.format.restricted_html.yml')) {
    // Disable Full HTML text format (restricted_html).
    $restricted_html_format_config = \Drupal::service('config.factory')->getEditable('filter.format.restricted_html');
    $restricted_html_format_config_file = \Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/filter.format.restricted_html.yml';
    $restricted_html_format_config_content = file_get_contents($restricted_html_format_config_file);
    $restricted_html_format_config_content_data = (array) Yaml::parse($restricted_html_format_config_content);
    $restricted_html_format_config->setData($restricted_html_format_config_content_data)->save();

    $restricted_html_editor_config = \Drupal::service('config.factory')->getEditable('editor.editor.restricted_html');
    $restricted_html_editor_config_file = \Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/editor.editor.restricted_html.yml';
    $restricted_html_editor_config_content = file_get_contents($restricted_html_editor_config_file);
    $restricted_html_editor_config_content_data = (array) Yaml::parse($restricted_html_editor_config_content);
    $restricted_html_editor_config->setData($restricted_html_editor_config_content_data)->save();

    $update_message = t('<b>WARNING:</b><br /><p>The "Full HTML" text format was mistakenly referred to by its machine name (restricted_html), this is confusing and wrong. Therefore, this filter has been deprecated in favor of better naming to become "HTML code" (code_html).</p><p>Please make sure to revise your content if it was using the "Full HTML" text format. You can enable it again if you like, or switch to use the new "HTML code" text format.</p>');
    \Drupal::logger('varbase_editor')->notice($update_message);
    \Drupal::messenger()->addWarning($update_message);
  }
}

/**
 * Enable pathologic module.
 *
 * Enable image resize filter module.
 * Enable ckeditor bidi module.
 * Enable pathologic module.
 */
function varbase_editor_update_8002() {
  // Enable pathologic module.
  if (!\Drupal::moduleHandler()->moduleExists('pathologic')) {
    \Drupal::service('module_installer')->install(['pathologic'], FALSE);
  }

  // Enable ckeditor bidi module.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor_bidi')) {
    \Drupal::service('module_installer')->install(['ckeditor_bidi'], FALSE);
  }

  // Enable pathologic module.
  if (!\Drupal::moduleHandler()->moduleExists('pathologic')) {
    \Drupal::service('module_installer')->install(['pathologic'], FALSE);
  }
}

/**
 * Enable CKEditor media embed module.
 */
function varbase_editor_update_8003() {

}

/**
 * Update "Rich editor" to use the CKEditor media embed button.
 */
function varbase_editor_update_8004() {
  // Update "Rich editor" editor config.
  $full_html_editor_config = \Drupal::service('config.factory')->getEditable('editor.editor.full_html');
  $full_html_editor_config_file = \Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/editor.editor.full_html.yml';
  $full_html_editor_config_content = file_get_contents($full_html_editor_config_file);
  $full_html_editor_config_content_data = (array) Yaml::parse($full_html_editor_config_content);
  $full_html_editor_config->setData($full_html_editor_config_content_data)->save();

  // Update "Rich editor" filter format config.
  $full_html_format_config = \Drupal::service('config.factory')->getEditable('filter.format.full_html');
  $full_html_format_config_file = \Drupal::root() . '/' . drupal_get_path('module', 'varbase_editor') . '/config/install/filter.format.full_html.yml';
  $full_html_format_config_content = file_get_contents($full_html_format_config_file);
  $full_html_format_config_content_data = (array) Yaml::parse($full_html_format_config_content);
  $full_html_format_config->setData($full_html_format_config_content_data)->save();
}

/**
 * Issue #3037311: Update [Image Resize Filter] module.
 *
 * And update [Varbase Editor] to configure [Rich editor, Simple editor] to
 * use for local and remote images and not to use for [HTML coder].
 */
function varbase_editor_update_8005() {

}

/**
 * Issue #3085555: Have the [Replaces global and entity tokens.
 *
 * With their values] filter only for HTML Editor (code filter) text format.
 */
function varbase_editor_update_8701() {
  if (!\Drupal::moduleHandler()->moduleExists('token_filter')) {
    \Drupal::service('module_installer')->install(['token_filter'], FALSE);
  }

  // Update "HTML code" editor config.
  // ------------------------------------------------------------------------.
  // #  token_filter:
  // #    id: token_filter
  // #    provider: token_filter
  // #    status: true
  // #    weight: 0
  // #    settings:
  // #      replace_empty: '1'
  // #
  // # .
  $code_html_editor_config = \Drupal::service('config.factory')->getEditable('filter.format.code_html');
  if (isset($code_html_editor_config)) {
    $code_html_editor_config_data = $code_html_editor_config->get();

    if (!isset($code_html_editor_config_data['filters']['token_filter'])) {

      $code_html_editor_config_data['dependencies']['module'][] = 'token_filter';

      $code_html_editor_config_data['filters']['token_filter'] = [
        'id' => 'token_filter',
        'provider' => 'token_filter',
        'status' => TRUE,
        'weight' => 0,
        'settings' => [
          'replace_empty' => '1',
        ],
      ];

      $code_html_editor_config->setData($code_html_editor_config_data)->save(TRUE);

    }
  }
}

/**
 * Issue #3157438: Fix CKEditor Media Embed not working on any https env.
 */
function varbase_editor_update_8702() {

}
