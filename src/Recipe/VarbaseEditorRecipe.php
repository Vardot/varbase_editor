<?php

declare(strict_types=1);

namespace Drupal\varbase_editor\Recipe;

use Symfony\Component\Yaml\Yaml;
use Drupal\Component\Serialization\Yaml as SerializationYaml;
use Drupal\Core\Recipe\Recipe;

/**
 * Contains helper methods for interacting with CKEdiotr 5 recipes.
 */
class VarbaseEditorRecipe {

  /**
   * Get Recipe as String.
   *
   * @param string $recipyPath
   *   The path to the recipe folder.
   *
   * @return string
   *   Get text content of the recipe.yml file.
   */
  public static function getRecipeString(string $recipyPath): string {
    if (!str_ends_with($recipyPath, '/recipe.yml')) {
      if (!str_ends_with($recipyPath, '/')) {
        $recipyPath = $recipyPath . '/recipe.yml';
      }
      else {
        $recipyPath = $recipyPath . 'recipe.yml';
      }
    }

    return file_get_contents($recipyPath);
  }

  /**
   * Get Recipe as array.
   *
   * @param string $recipyPath
   *   The path to the recipe folder.
   *
   * @return array
   *   Get array data for the recipe.
   */
  public static function getRecipeData(string $recipyPath): array {
    if (!str_ends_with($recipyPath, '/recipe.yml')) {
      if (str_ends_with($recipyPath, '/')) {
        $recipyPath .= 'recipe.yml';
      }
      else {
        $recipyPath .= '/recipe.yml';
      }
    }

    return (array) Yaml::parse(file_get_contents($recipyPath));
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
   * Get item postion in an editor.
   *
   * @param string $editorConfigName
   *   The editor config name.
   * @param string $itemName
   *   The item name.
   *
   * @return int
   */
  public static function getItemPostion(string $editorConfigName, string $itemName): int {
    $full_html_toolbar_items = \Drupal::service('config.factory')->getEditable($editorConfigName)->get('settings.toolbar.items');

    $item_postion = -1;
    if (isset($full_html_toolbar_items) && is_array($full_html_toolbar_items)) {
      foreach ($full_html_toolbar_items as $item_index => $item) {
        if ($item == $itemName) {
          $item_postion = $item_index;
          break;
        }
      }
    }

    return $item_postion;

  }

  /**
   * Set Item Postion in an editor.
   *
   * @param array $recipeData
   *   The data array for a recipe.
   * @param string $editorConfigName
   *   The editor config name.
   * @param int $itemPosition
   *   The postion of the item.
   *
   * @return void
   */
  public static function setItemPosition(array &$recipeData, string $editorConfigName, int $itemPosition): void {
    if ($itemPosition != -1) {
      $recipeData['config']['actions'][$editorConfigName]['addItemToToolbar']['position'] = $itemPosition;
    }
  }

  /**
   * Item foudn in Toolbar.
   *
   * @param string $editorConfigName
   *   The editor config name.
   * @param string $itemName
   *   The item name
   *
   * @return bool
   *   true when found.
   */
  public static function itemFoundInToolbar(string $editorConfigName, string $itemName): bool {

    if (self::getItemPostion($editorConfigName, $itemName) == -1) {
      return FALSE;
    }

    return TRUE;
  }

}
