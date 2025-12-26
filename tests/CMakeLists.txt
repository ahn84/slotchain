
add_executable(test_static test_static_pipeline.cpp)
target_link_libraries(test_static PRIVATE slotchain::slotchain)
add_test(NAME static COMMAND test_static)

add_executable(test_runtime test_runtime_pipeline.cpp)
target_link_libraries(test_runtime PRIVATE slotchain::slotchain)
add_test(NAME runtime COMMAND test_runtime)

add_executable(test_disconnect test_disconnect.cpp)
target_link_libraries(test_disconnect PRIVATE slotchain::slotchain)
add_test(NAME disconnect COMMAND test_disconnect)
