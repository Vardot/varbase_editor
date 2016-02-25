; Varbase Editor Makefile

api = 2
core = 7.x

; WYSIWYG Improvements

projects[ace_editor][version] = 1.5
projects[ace_editor][subdir] = contrib
projects[ace_editor][patch][2645848] = "http://www.drupal.org/files/issues/ace_editor-autocomplete_checkbox_classname_2645848-3.patch"

projects[better_formats][version] = "1.0-beta2"
projects[better_formats][subdir] = contrib

projects[ckeditor][version] = 1.17
projects[ckeditor][subdir] = contrib

projects[media_ckeditor][version] = "2.x-dev"
projects[media_ckeditor][download][type] = "git"
projects[media_ckeditor][download][url] = "http://git.drupal.org/project/media_ckeditor.git"
projects[media_ckeditor][download][revision] = "7409f2c0923f7bd81e91303a9d6032505d89d1cf"
projects[media_ckeditor][subdir] = contrib
projects[media_ckeditor][patch][2333855] = "http://www.drupal.org/files/issues/media_ckeditor-module-browser-tabs-2333855-13.patch"
projects[media_ckeditor][patch][2352573] = "http://www.drupal.org/files/issues/ckeditor_media_wysiwyg-2352573-7.patch"

projects[pathologic][version] = 2.12
projects[pathologic][subdir] = contrib

projects[token_filter][version] = 1.1
projects[token_filter][subdir] = contrib

projects[wysiwyg_filter][version] = 1.6-rc3
projects[wysiwyg_filter][subdir] = contrib

;;;;;;;;;;;;;;;;;;;;;
;; Libraries
;;;;;;;;;;;;;;;;;;;;;

libraries[ace][download][type] = "get"
libraries[ace][download][url] = "http://github.com/ajaxorg/ace-builds/archive/v1.2.0.tar.gz"

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.5.7/ckeditor_4.5.7_full.zip"

libraries[widget][download][type] = "get"
libraries[widget][download][url] = "http://download.ckeditor.com/widget/releases/widget_4.5.7.zip"
libraries[widget][destination] = "modules/contrib/ckeditor/plugins/"

libraries[lineutils][download][type] = "get"
libraries[lineutils][download][url] = "http://download.ckeditor.com/lineutils/releases/lineutils_4.5.7.zip"
libraries[lineutils][destination] = "modules/contrib/ckeditor/plugins/"
