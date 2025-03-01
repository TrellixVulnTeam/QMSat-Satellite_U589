Feature: Non feature files keep their level folder

  During copy of the feature folder in new folder the non feature files are also
  copied and keep their own hierarchy level

  Scenario: Files in a subfolder
    Given an empty folder
    And   the folder named "Subfolder"
    And   a file named "Subfolder\\Feature to move.feature" with content
    And   a file named "Subfolder\\txt file to move.txt" with content
    And   a file named "image to move.png" with content
    When  invoking Gherkin2Cpp with option "--output-feature-dir=gherkin2cpp\\MovedFolder"
    Then  file Feature to move.feature is in gherkin2cpp\\MovedFolder\\Subfolder folder instead
    Then  file txt file to move.txt is in gherkin2cpp\\MovedFolder\\Subfolder folder instead
    Then  file image to move.png is in gherkin2cpp\\MovedFolder folder instead


