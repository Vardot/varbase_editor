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

  // Get the first postion for wrapping.
  $first_wrapping_position = VarbaseEditorRecipe::getItemPostion('editor.editor.full_html', '-');

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'fullScreen')) {
    // Add fullScreen to Rich Editor, positioned before the first wrapping.
    $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-fullscreen-to-rich-editor');
    VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $first_wrapping_position);
    $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
    RecipeRunner::processRecipe($recipe);
  }

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'showBlocks')) {
    // Add showBlocks to Rich Editor, positioned before the first wrapping.
    $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-showblocks-to-rich-editor');
    VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $first_wrapping_position);
    $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
    RecipeRunner::processRecipe($recipe);
  }

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'specialCharacters')) {
    if (VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'removeFormat')) {
      // Get the postion for the Remove Format button.
      $remove_format_position = VarbaseEditorRecipe::getItemPostion('editor.editor.full_html', 'removeFormat');

      // Add specialCharacters after removeFormat in Rich Editor.
      $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-specialcharacters-to-rich-editor');
      VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $remove_format_position + 1);
      $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
      RecipeRunner::processRecipe($recipe);

      // Add a divider as (vertical separator) after removeFormat in the Rich Editor.
      $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-divider-to-rich-editor');
      VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $remove_format_position + 1);
      $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
      RecipeRunner::processRecipe($recipe);
    }
    else {
      // Add specialCharacters at the end of all items in the Rich Editor.
      $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-specialcharacters-to-rich-editor');
      RecipeRunner::processRecipe($recipe);
    }
  }

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'wproofreader')
    || !VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'findAndReplace')) {

    // Add a divider as (vertical separator) at the end of all items in the Rich Editor.
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-divider-to-rich-editor');
    RecipeRunner::processRecipe($recipe);
  }

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'wproofreader')) {
    // Add wproofreader at the end of all items in the Rich Editor.
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-wproofreader-to-rich-editor');
    RecipeRunner::processRecipe($recipe);
  }

  if (!VarbaseEditorRecipe::itemFoundInToolbar('editor.editor.full_html', 'findAndReplace')) {
    // Add findAndReplace at the end of all items in the Rich Editor.
    $recipe = Recipe::createFromDirectory($module_path . '/recipes/add-findandreplace-to-rich-editor');
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
    // Get the postion for thespecialCharacters button.
    $special_characters_position = VarbaseEditorRecipe::getItemPostion('editor.editor.full_html', 'specialCharacters');

    // Add a divider as (vertical separator) after removeFormat in the Rich Editor.
    $recipe_data = VarbaseEditorRecipe::getRecipeData($module_path . '/recipes/add-emoji-to-rich-editor');
    VarbaseEditorRecipe::setItemPosition($recipe_data, 'editor.editor.full_html', $special_characters_position + 1);
    $recipe = VarbaseEditorRecipe::createRecipe($recipe_data);
    RecipeRunner::processRecipe($recipe);
  }

}
