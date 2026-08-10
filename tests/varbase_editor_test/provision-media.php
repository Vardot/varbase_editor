<?php

/**
 * @file
 * Provisions the Media scaffolding for the Varbase Editor varbase-e2e test site.
 *
 * Creates what the Rich editor (full_html) format config depends on.
 *
 * On a full Varbase site the media view modes (media.large / medium / small /
 * original) and the image media type come from Varbase Media. The plain test
 * site (Standard profile) does not ship them, so recipes/default's config
 * import of filter.format.full_html would fail with "Missing bundle entity,
 * entity type media_type, entity id image". Create the minimum needed here.
 *
 * Run with:
 *   drush php:script tests/varbase_editor_test/provision-media.php
 */

use Drupal\Core\Entity\Entity\EntityViewMode;
use Drupal\media\Entity\MediaType;

// Media view modes referenced by the Rich editor (full_html) format config.
foreach (['large', 'medium', 'small', 'original'] as $view_mode) {
  $id = 'media.' . $view_mode;
  if (!\Drupal::entityTypeManager()->getStorage('entity_view_mode')->load($id)) {
    EntityViewMode::create([
      'id' => $id,
      'label' => ucfirst($view_mode),
      'targetEntityType' => 'media',
    ])->save();
  }
}

// Image media type referenced by the Rich editor allowed_media_types.
if (!\Drupal::entityTypeManager()->getStorage('media_type')->load('image')) {
  $media_type = MediaType::create([
    'id' => 'image',
    'label' => 'Image',
    'source' => 'image',
  ]);
  $media_type->save();
  $source = $media_type->getSource();
  $source_field = $source->createSourceField($media_type);
  $source_field->getFieldStorageDefinition()->save();
  $source_field->save();
  $media_type->set('source_configuration', [
    'source_field' => $source_field->getName(),
  ])->save();
}

// phpcs:ignore Drupal.Semantics.FunctionT.NotLiteralString
print "Provisioned media view modes + image media type for Varbase Editor.\n";
