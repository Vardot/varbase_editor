; Varbase Editor Makefile

api = 2
core = 8.x

; Defaults
defaults[projects][subdir] = "contrib"

; WYSIWYG Improvements

projects[anchor_link][type] = module
projects[anchor_link][version] = 1.5

projects[linkit][type] = module
projects[linkit][version] = 4.3

projects[entity_embed][type] = module
projects[entity_embed][version] = 1.0-beta2

projects[pathologic][type] = module
projects[pathologic][download][url] = https://git.drupal.org/project/pathologic.git
projects[pathologic][download][revision] = e0473546e51cbeaa3acb34e3208a0c503ca85613
projects[pathologic][download][branch] = 8.x-1.x

projects[ckeditor_bidi][type] = module
projects[ckeditor_bidi][version] = 2.0

projects[ace_editor][type] = module
projects[ace_editor][download][url] = https://git.drupal.org/project/ace_editor.git
projects[ace_editor][download][revision] = 55dc97d7fcc1aba55a16176f94d72a8ba7002c72
projects[ace_editor][download][branch] = 8.x-1.x

projects[embed][type] = module
projects[embed][version] = 1.0

projects[video_embed_field][type] = module
projects[video_embed_field][version] = 1.5

projects[image_resize_filter][type] = module
projects[image_resize_filter][download][url] = https://git.drupal.org/project/image_resize_filter.git
projects[image_resize_filter][download][revision] = c3f4b23b02005859092aaff746b9f21b794adc58
projects[image_resize_filter][download][branch] = 8.x-1.x

;;;;;;;;;;;;;;;;;;;;;
;; Libraries
;;;;;;;;;;;;;;;;;;;;;

libraries[ace][directory_name] = "ace"
libraries[ace][download][type] = "get"
libraries[ace][download][url] = "http://github.com/ajaxorg/ace-builds/archive/v1.2.6.tar.gz"
libraries[ace][destination] = "modules/contrib/ace_editor/libraries/"