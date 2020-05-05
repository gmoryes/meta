project(tests)

enable_testing()

SET(
        SRC
        is_optional_tests.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}) 