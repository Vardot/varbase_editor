@varbase_editor @formats
Feature: Varbase Editor - text formats with CKEditor 5
  As a site administrator
  I want the Varbase Simple editor and Rich editor formats running on CKEditor 5

  Background:
    Given I am a logged in user with the "Webmaster" user

  Scenario: The Simple editor format uses CKEditor 5
    When I go to "/admin/config/content/formats"
    Then I should see "Simple editor"
    And I should see "CKEditor 5"

  Scenario: The Rich editor format is available
    When I go to "/admin/config/content/formats"
    Then I should see "Rich editor"

  Scenario: The HTML code format is available
    When I go to "/admin/config/content/formats"
    Then I should see "HTML code"

  Scenario: The Simple editor format can be configured
    When I go to "/admin/config/content/formats/manage/basic_html"
    Then I should see "Simple editor"
    And I should see "Text editor"
