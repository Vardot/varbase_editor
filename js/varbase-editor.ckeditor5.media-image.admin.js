(function (Drupal, $, once) {
  // Varbase Editor media image behaviors.
  Drupal.behaviors.varbaseEditorMediaImage = {
    attach: function (context, settings) {
      // Check if there are CKEditor 5 instances available.
      if (Drupal.CKEditor5Instances) {
        // Iterate over each CKEditor 5 instance.
        Drupal.CKEditor5Instances.forEach(function (editor) {

          // Listen for the 'imageLoaded' event on the editing view.
          editor.editing.view.document.on('imageLoaded', () => {
            // Use 'once' to ensure the following code executes only once per context.
            $(once('varbase-editor-image-load-execution', '.ck-editor__editable', context)).each(function (index) {
              // Get the current selection in the editor.
              const selection = editor.model.document.selection;
              const selectedElement = selection.getSelectedElement();

              // Check if the selected element is a media element.
              if (selectedElement && selectedElement.is('element', 'drupalMedia')) {
                // Determine if the selected media is an image.
                const isImageMedia = !!selectedElement.getAttribute('drupalMediaIsImage');

                if (isImageMedia) {
                  // Get the commands for modifying view mode and resizing media.
                  const viewModeCommand = editor.commands.get('drupalElementStyle');
                  const resizeCommand = editor.commands.get('resizeMediaImage');

                  // Ensure that the commands are executed only once.
                  if (resizeCommand.value == null) {
                    // Execute commands.
                    viewModeCommand.execute({ value: 'large', group: 'viewMode' });
                    resizeCommand.execute({ width: '50%' });
                  }
                }
              }
            });
          });
        });
      }
    }
  };
}(Drupal, jQuery, once));
