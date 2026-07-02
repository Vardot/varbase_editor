@varbase_editor @ckeditor5
Feature: Varbase Editor - CKEditor 5 in content forms
  As a content editor
  I want CKEditor 5 on the body field

  Background:
    Given I am a logged in user with the "Webmaster" user

  Scenario: The article body uses CKEditor 5
    When I go to "/node/add/article"
    Then I should see "Create Article"
    And ".ck-editor" should be visible

  Scenario: The article body offers the Varbase text formats
    When I go to "/node/add/article"
    Then I should see "Basic HTML"
    And I should see "Full HTML"
