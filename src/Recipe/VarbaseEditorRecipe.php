<?php

declare(strict_types=1);

namespace Drupal\varbase_editor\Recipe;

use Drupal\Component\Serialization\Yaml as SerializationYaml;
use Drupal\Core\Recipe\Recipe;

/**
 * Contains helper methods for interacting with CKEditor 5 recipes.
 */
class VarbaseEditorRecipe {

  /**
   * Get Recipe as String.
   *
   * @param string $recipePath
   *   The path to the recipe folder.
   *
   * @return string
   *   Get text content of the recipe.yml file.
   */
  public static function getRecipeString(string $recipePath): string {
    if (!str_ends_with($recipePath, '/recipe.yml')) {
      if (!str_ends_with($recipePath, '/')) {
        $recipePath = $recipePath . '/recipe.yml';
      }
      else {
        $recipePath = $recipePath . 'recipe.yml';
      }
    }

    return file_get_contents($recipePath);
  }

  /**
   * Get Recipe as array.
   *
   * @param string $recipePath
   *   The path to the recipe folder.
   *
   * @return array
   *   Get array data for the recipe.
   */
  public static function getRecipeData(string $recipePath): array {
    if (!str_ends_with($recipePath, '/recipe.yml')) {
      if (str_ends_with($recipePath, '/')) {
        $recipePath .= 'recipe.yml';
      }
      else {
        $recipePath .= '/recipe.yml';
      }
    }

    return (array) SerializationYaml::decode(file_get_contents($recipePath));
  }

  /**
   * Creates a recipe from string or an array.
   *
   * @param string|array<mixed> $data
   *   The contents of recipe.yml. If passed as an array, will be encoded to
   *   YAML.
   * @param string|null $machine_name
   *   The machine name for the recipe. Will be used as the directory name.
   *
   * @return \Drupal\Core\Recipe\Recipe
   *   The recipe object.
   */
  public static function createRecipe(string|array $data, ?string $machine_name = NULL): Recipe {
    if (is_array($data)) {
      $data = SerializationYaml::encode($data);
    }
    $temp_recipes_dir = \Drupal::service('file_system')->getTempDirectory() . '/recipes';

    if ($machine_name === NULL) {
      $dir = uniqid($temp_recipes_dir . '/');
    }
    else {
      $dir = $temp_recipes_dir . '/' . $machine_name;
    }
    mkdir($dir, recursive: TRUE);
    file_put_contents($dir . '/recipe.yml', $data);

    return Recipe::createFromDirectory($dir);
  }

  /**
   * Get item position in an editor.
   *
   * @param string $editorConfigName
   *   The editor config name.
   * @param string $itemName
   *   The item name.
   *
   * @return int
   *   Return the item position as an integer number.
   */
  public static function getItemPosition(string $editorConfigName, string $itemName): int {
    $full_html_toolbar_items = \Drupal::service('config.factory')->getEditable($editorConfigName)->get('settings.toolbar.items');

    $item_position = -1;
    if (isset($full_html_toolbar_items) && is_array($full_html_toolbar_items)) {
      foreach ($full_html_toolbar_items as $item_index => $item) {
        if ($item == $itemName) {
          $item_position = $item_index;
          break;
        }
      }
    }

    return $item_position;

  }

  /**
   * Set Item Position in an editor.
   *
   * @param array $recipeData
   *   The data array for a recipe.
   * @param string $editorConfigName
   *   The editor config name.
   * @param int $itemPosition
   *   The position of the item.
   */
  public static function setItemPosition(array &$recipeData, string $editorConfigName, int $itemPosition): void {
    if ($itemPosition != -1) {
      $recipeData['config']['actions'][$editorConfigName]['addItemToToolbar']['position'] = $itemPosition;
    }
  }

  /**
   * Item found in Toolbar.
   *
   * @param string $editorConfigName
   *   The editor config name.
   * @param string $itemName
   *   The item name.
   *
   * @return bool
   *   true when found.
   */
  public static function itemFoundInToolbar(string $editorConfigName, string $itemName): bool {

    if (self::getItemPosition($editorConfigName, $itemName) == -1) {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Is the block styles in the text format not changed.
   *
   * @param string $editorConfigName
   *   The editor config name.
   * @param array $blockStyles
   *   The CKEditor 5 styles for the text format.
   *
   * @return bool
   *   true when old config is not changed yet.
   */
  public static function blockStylesNotChanged(string $editorConfigName, array $blockStyles): bool {
    $currentBlockStyles = \Drupal::service('config.factory')->getEditable($editorConfigName)->get('settings.plugins.ckeditor5_style.styles');

    if ($blockStyles === $currentBlockStyles) {
      return TRUE;
    }
    else {
      return FALSE;
    }

  }

}
