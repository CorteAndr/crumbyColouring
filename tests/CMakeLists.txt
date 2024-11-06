enable_testing()

find_package(GTest REQUIRED)

add_executable(tests
        tests.cpp)

target_link_libraries(tests PRIVATE checker graphLoader GTest::GTest GTest::Main)

add_test(NAME Testing COMMAND tests)