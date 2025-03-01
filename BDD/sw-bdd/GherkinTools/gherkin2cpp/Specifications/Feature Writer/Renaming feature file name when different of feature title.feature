Feature: Renaming feature file name when different of feature title

    The feature writer will change the feature file name to match to feature title (content of file).

  Scenario: File name match with feature title
    Given an empty folder
      And a feature file named "I match the feature title.feature" with content
          """
          Feature: I match the feature title
            Scenario: 01
              Given nothing
              Then you get nothing
          """
    When invoking Gherkin2Cpp with option " "
    Then feature title and feature file name matches


  Scenario: File name differs from feature title
    Given an empty folder
      And a feature file named "I do not match.feature" with content
          """
          Feature: Please match me
            Scenario: 02
              Given nothing
              Then you get nothing
          """
    When invoking Gherkin2Cpp with option " "
    Then feature title and feature file name matches



