; Varbase Editor Makefile

api = 2
core = 7.x

; WYSIWYG Improvements

projects[ace_editor][version] = 1.7
projects[ace_editor][subdir] = contrib

projects[better_formats][version] = "1.0-beta2"
projects[better_formats][subdir] = contrib

projects[ckeditor][version] = 1.17
projects[ckeditor][subdir] = contrib

projects[media_ckeditor][version] = 2.0-alpha3
projects[media_ckeditor][subdir] = contrib

projects[pathologic][version] = 3.1
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
