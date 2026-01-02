include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES *.cpp)
add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests 
    PRIVATE 
        nasdaq_itch_parser 
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
