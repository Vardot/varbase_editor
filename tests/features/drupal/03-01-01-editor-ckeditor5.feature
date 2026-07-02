@varbase_editor @ckeditor5
Feature: Varbase Editor - CKEditor 5 configuration
  As a content editor
  I want the Varbase text formats wired to the CKEditor 5 editor

  Background:
    Given I am a logged in user with the "Webmaster" user

  Scenario: The Simple editor format is configured with CKEditor 5
    When I go to "/admin/config/content/formats/manage/basic_html"
    Then I should see "Text editor"
    And I should see "CKEditor 5"

  Scenario: The Rich editor format is configured with CKEditor 5
    When I go to "/admin/config/content/formats/manage/full_html"
    Then I should see "Text editor"
    And I should see "CKEditor 5"
