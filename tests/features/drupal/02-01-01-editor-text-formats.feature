@varbase_editor @formats
Feature: Varbase Editor - text formats with CKEditor 5
  As a site administrator
  I want the Varbase Basic HTML and Full HTML formats running on CKEditor 5

  Background:
    Given I am a logged in user with the "Webmaster" user

  Scenario: The Basic HTML format uses CKEditor 5
    When I go to "/admin/config/content/formats"
    Then I should see "Basic HTML"
    And I should see "CKEditor 5"

  Scenario: The Full HTML format is available
    When I go to "/admin/config/content/formats"
    Then I should see "Full HTML"

  Scenario: The Basic HTML format can be configured
    When I go to "/admin/config/content/formats/manage/basic_html"
    Then I should see "Basic HTML"
    And I should see "Text editor"
