find_package(GTest REQUIRED)

add_executable(prunedTests
        prunedTests.cpp)

target_link_libraries(prunedTests PRIVATE naiveCrumbyColouring prunedCrumbyColouring GTest::GTest GTest::Main)

add_test(NAME PrunedTest COMMAND prunedTests)