# Fetch GoogleTest as dependency
include(FetchContent)
FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # Choose a stable release version
)
FetchContent_MakeAvailable(gtest)

add_executable(prunedTests
        prunedTests.cpp)

target_link_libraries(prunedTests PRIVATE naiveCrumbyColouring prunedCrumbyColouring naiveCrumbyColouring gtest gtest_main)

add_test(NAME PrunedTest COMMAND prunedTests)