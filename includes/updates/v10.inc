<?php

/**
 * @file
 * Contains varbase_editor_update_10###(s) hook updates.
 */

use Drupal\Core\Recipe\Recipe;
use Drupal\Core\Recipe\RecipeRunner;
use Drupal\varbase_editor\Recipe\VarbaseEditorRecipe;

/**
 * Issue #3405819: Add the Anchor Link ~3 module.
 *
 * Configure the CKEditor 5 Rich Editor text format to use it.
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

/**
 * Issue #3442854: Add CKEditor 5 Paste Filter module to Varbase Editor.
 */
function varbase_editor_update_100002() {
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

/**
 * Issue #3460065: Add CKEditor Plug-in Pack module and enable.
 *
 * The fullscreen, find and replace, show blocks, and wproof reader plugins.
 */
function varbase_editor_update_100003() {
  $module_path = Drupal::service('module_handler')->getModule('varbase_editor')->getPath();

  $recipe = Recipe::createFromDirectory($module_path . '/recipes/updates/varbase_editor_update_100003');
  RecipeRunner::processRecipe($recipe);

  // Get the first position for wrapping.
  $first_wrapping_position = VarbaseEditorRecipe::getItemPosition('editor.editor.full_html', '-');

  // Add fullScreen to Rich Editor, positioned before the first wrapping.
  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'fullScreen')) {
    $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-fullscreen-to-rich-editor');
    VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $first_wrapping_position);
    $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
    RecipeRunner::processRecipe($recipe);
  }

  // Add showBlocks to Rich Editor, positioned before the first wrapping.
  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'showBlocks')) {
    $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-showblocks-to-rich-editor');
    VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $first_wrapping_position);
    $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
    RecipeRunner::processRecipe($recipe);
  }

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'specialCharacters')) {
    if (VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'removeFormat')) {
      // Get the position for the Remove Format button.
      $remove_format_position = VarbaseEditorRecipe::getItemPosition('editor.editor.full_html', 'removeFormat');

      // Add a divider as (vertical separator) after removeFormat
      // in the Rich Editor.
      $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-divider-to-rich-editor');
      VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $remove_format_position + 1);
      $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
      RecipeRunner::processRecipe($recipe);

      // Add specialCharacters after removeFormat in Rich Editor.
      $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-specialcharacters-to-rich-editor');
      VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $remove_format_position + 2);
      $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
      RecipeRunner::processRecipe($recipe);
    }
    else {
      // Add specialCharacters at the end of all items in the Rich Editor.
      $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-specialcharacters-to-rich-editor');
      RecipeRunner::processRecipe($recipe);
    }
  }

  // Add a divider as (vertical separator) at the end of all items
  // in the Rich Editor.
  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'wproofreader')
    || !VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'findAndReplace')) {
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-divider-to-rich-editor');
    RecipeRunner::processRecipe($recipe);
  }

  // Add wproofreader at the end of all items in the Rich Editor.
  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'wproofreader')) {
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-wproofreader-to-rich-editor');
    RecipeRunner::processRecipe($recipe);
  }

  // Add findAndReplace at the end of all items in the Rich Editor.
  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'findAndReplace')) {
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-findandreplace-to-rich-editor');
    RecipeRunner::processRecipe($recipe);
  }

  // Add wrapping at the end of all items in the Simple Editor.
  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.basic_html', '-')) {
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-wrapping-to-simple-editor');
    RecipeRunner::processRecipe($recipe);
  }

}

/**
 * Issue #3462267: Add CKEditor(5) Emoji module to CKEditor 5 in Varbase Editor.
 *
 * And enable it by default.
 */
function varbase_editor_update_100004() {
  $module_path = Drupal::service('module_handler')->getModule('varbase_editor')->getPath();

  $recipe = Recipe::createFromDirectory($module_path . '/recipes/updates/varbase_editor_update_100004');
  RecipeRunner::processRecipe($recipe);

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'Emoji')) {
    // Get the position for the specialCharacters button.
    $special_characters_position = VarbaseEditorRecipe::getItemPosition('editor.editor.full_html', 'specialCharacters');

    // Add a divider as (vertical separator) after removeFormat
    // in the Rich Editor.
    $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-emoji-to-rich-editor');
    VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $special_characters_position + 1);
    $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
    RecipeRunner::processRecipe($recipe);
  }

}

/**
 * Issue #3466509: Change the list of styles for heading.
 *
 * With display, callout, alert. And remove leftover BS3 and BS4 legacy
 * classes and logic in favor of the new logic in Bootstrap 5.
 */
function varbase_editor_update_100005() {

  $full_html_block_styles = [
    // Headings.
    ['label' => 'Display 1', 'element' => '<h2 class="display-1">'],
    ['label' => 'Display 2', 'element' => '<h2 class="display-2">'],
    ['label' => 'Display 3', 'element' => '<h3 class="display-3">'],
    ['label' => 'Display 4', 'element' => '<h4 class="display-4">'],

    // Callouts.
    ['label' => 'Callout', 'element' => '<div class="bs-callout">'],
    ['label' => 'Callout danger', 'element' => '<div class="bs-callout bs-callout-danger">'],
    ['label' => 'Callout warning', 'element' => '<div class="bs-callout bs-callout-warning">'],
    ['label' => 'Callout Info', 'element' => '<div class="bs-callout bs-callout-info">'],

    // Wells.
    ['label' => 'Well', 'element' => '<div class="well">'],
    ['label' => 'Well large', 'element' => '<div class="well well-lg">'],
    ['label' => 'Well small', 'element' => '<div class="well well-sm">'],

    // Alerts.
    ['label' => 'Alert success', 'element' => '<div class="alert alert-success">'],
    ['label' => 'Alert info', 'element' => '<div class="alert alert-info">'],
    ['label' => 'Alert warning', 'element' => '<div class="alert alert-warning">'],
    ['label' => 'Alert danger', 'element' => '<div class="alert alert-danger">'],

    // Cards.
    ['label' => 'Card primary', 'element' => '<div class="card bg-primary">'],
    ['label' => 'Card success', 'element' => '<div class="card bg-success">'],
    ['label' => 'Card info', 'element' => '<div class="card bg-info">'],
    ['label' => 'Card warning', 'element' => '<div class="card bg-warning">'],
    ['label' => 'Card danger', 'element' => '<div class="card bg-danger">'],
    ['label' => 'Card header', 'element' => '<div class="card-header">'],
    ['label' => 'Card title', 'element' => '<div class="card-title">'],
    ['label' => 'Card body', 'element' => '<div class="card-body">'],
    ['label' => 'Card footer', 'element' => '<div class="card-footer">'],
  ];

  // Apply the CKEditor 5 style changes on the Rich Editor text format
  // when old config is not changed.
  if (VarbaseEditorRecipe::blockStylesNotChanged('editor.editor.full_html', $full_html_block_styles)) {
    $module_path = Drupal::service('module_handler')->getModule('varbase_editor')->getPath();
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/updates/varbase_editor_update_100005');
    RecipeRunner::processRecipe($recipe);
  }

}

/**
 * Issue #3471017: Add Edit Media Entity in Modal module.
 *
 * And enable by default.
 */
function varbase_editor_update_100006() {
  $module_path = Drupal::service('module_handler')->getModule('varbase_editor')->getPath();

  $recipe = Recipe::createFromDirectory($module_path . '/recipes/updates/varbase_editor_update_100006');
  RecipeRunner::processRecipe($recipe);

}

/**
 * Issue #3471411: Reorder Heading and Style Buttons in CKEditor Toolbar items.
 */
function varbase_editor_update_100007() {

  $editor_config = \Drupal::service('config.factory')->getEditable('editor.editor.full_html');
  $editor_data = $editor_config->get();

  $reordered_full_html_toolbar_items = [];
  foreach ($editor_data['settings']['toolbar']['items'] as $toolbar_item) {

    if ($toolbar_item == 'style') {
      $reordered_full_html_toolbar_items[] = 'heading';
      $reordered_full_html_toolbar_items[] = 'style';
    }
    elseif ($toolbar_item == 'heading') {
      // Ignore, do nothing, as it was added before the style.
    }
    else {
      $reordered_full_html_toolbar_items[] = $toolbar_item;
    }
  }

  $editor_data['settings']['toolbar']['items'] = $reordered_full_html_toolbar_items;

  $editor_config->setData($editor_data)->save(TRUE);

}

/**
 * Issue #3460610: Add CKEditor Media Resize module.
 *
 * And integrate it with Dynamic Responsive Image (Drimage) – Improved.
 */
function varbase_editor_update_100008() {
  // Check if the ckeditor_media_resize module is not already installed.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor_media_resize')) {
    // Install the ckeditor_media_resize module.
    \Drupal::service('module_installer')->install(['ckeditor_media_resize'], FALSE);
  }

  // Load the configuration for the Full HTML text format.
  $full_html_editor_config = \Drupal::service('config.factory')->getEditable('filter.format.full_html');

  // Check if the configuration is available.
  if ($full_html_editor_config) {
    $full_html_editor_config_data = $full_html_editor_config->get();

    // Check if the ckeditor_media_resize filter is not already added.
    if (!isset($full_html_editor_config_data['filters']['ckeditor_media_resize'])) {
      // Add ckeditor_media_resize as a dependency for the Full HTML text format.
      $full_html_editor_config_data['dependencies']['module'][] = 'ckeditor_media_resize';

      // Enable the "Limit allowed HTML tags and correct faulty HTML" filter.
      $new_allowed_html = '<a id target rel class="ck-anchor" href title data-entity-type data-entity-uuid data-entity-substitution> <br> <p class="bs-callout alert alert-success bs-callout-info alert-info bs-callout-warning alert-warning bs-callout-danger alert-danger text-align-left text-align-center text-align-right text-align-justify"> <h2 class="display-1 display-2 display-3 display-4 display-5 display-6 text-align-left text-align-center text-align-right text-align-justify"> <h3 class="display-1 display-2 display-3 display-4 display-5 display-6 text-align-left text-align-center text-align-right text-align-justify"> <h4 class="display-1 display-2 display-3 display-4 display-5 display-6 text-align-left text-align-center text-align-right text-align-justify"> <h5 class="display-1 display-2 display-3 display-4 display-5 display-6 text-align-left text-align-center text-align-right text-align-justify"> <h6 class="display-1 display-2 display-3 display-4 display-5 display-6 text-align-left text-align-center text-align-right text-align-justify"> <div class="text-align-left text-align-center text-align-right text-align-justify"> <span> <strong> <em> <u> <code class="language-*"> <pre class="text-align-left text-align-center text-align-right text-align-justify"> <s> <sub> <sup> <blockquote> <ul> <ol reversed start> <li> <hr> <table> <tr> <td rowspan colspan> <th rowspan colspan> <thead> <tbody> <tfoot> <caption> <drupal-media data-entity-type data-entity-uuid alt data-view-mode data-caption data-align data-media-width> <figure class> <oembed url> <drupal-entity alt title data-align data-caption data-entity-embed-display data-entity-embed-display-settings data-view-mode data-entity-uuid data-langcode data-embed-button="gallery media node" data-entity-type="media node">';

      // Merge the new allowed HTML tags with the existing ones if they already exist.
      if ($full_html_editor_config_data['filters']['filter_html']['settings']['allowed_html'] == '') {
        $final_allowed_html = $new_allowed_html;
      }
      else {
        $old_allowed_html = $full_html_editor_config_data['filters']['filter_html']['settings']['allowed_html'];
        $final_allowed_html = varbase_editor__merge_allowed_html($old_allowed_html, $new_allowed_html);
      }

      // Enable the filter and set the allowed HTML tags.
      $full_html_editor_config_data['filters']['filter_html']['status'] = TRUE;
      $full_html_editor_config_data['filters']['filter_html']['settings']['allowed_html'] = $final_allowed_html;

      // The ckeditor_media_resize filter needs to run before the Embed media filter.
      $filter_resize_media_weight = -40;
      if (isset($full_html_editor_config_data['filters']['media_embed'])
        && $full_html_editor_config_data['filters']['media_embed']['status'] == TRUE) {

        $filter_resize_media_weight = ((int) $full_html_editor_config_data['filters']['media_embed']['weight']) - 1;
      }

      // Enable the ckeditor_media_resize filter in the Full HTML text format.
      $full_html_editor_config_data['filters']['filter_resize_media'] = [
        'id' => 'filter_resize_media',
        'provider' => 'ckeditor_media_resize',
        'status' => TRUE,
        'weight' => $filter_resize_media_weight,
        'settings' => [],
      ];

      // Save the updated configuration.
      $full_html_editor_config->setData($full_html_editor_config_data)->save(TRUE);
    }
  }

  // Load the configuration for the Full HTML editor.
  $editor_full_html_config = \Drupal::service('config.factory')->getEditable('editor.editor.full_html');

  // Check if the configuration is available.
  if ($editor_full_html_config) {
    $editor_full_html_config_data = $editor_full_html_config->get();

    // Check if the ckeditor_media_resize_mediaResize plugin is not already added.
    if (!isset($editor_full_html_config_data['settings']['plugins']['ckeditor_media_resize_mediaResize'])) {
      // Add the ckeditor_media_resize_mediaResize plugin with its settings.
      $editor_full_html_config_data['settings']['plugins']['ckeditor_media_resize_mediaResize'] = [
        'apply_image_styles' => TRUE,
        'image_styles' => [
          'cke_media_resize_small',
          'cke_media_resize_medium',
          'cke_media_resize_large',
          'cke_media_resize_xl',
        ],
      ];

      // Save the updated configuration.
      $editor_full_html_config->setData($editor_full_html_config_data)->save(TRUE);
    }
  }
}
