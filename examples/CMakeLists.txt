
add_executable(example_static static_pipeline.cpp)
target_link_libraries(example_static PRIVATE slotchain::slotchain)

add_executable(example_runtime runtime_pipeline.cpp)
target_link_libraries(example_runtime PRIVATE slotchain::slotchain)

add_executable(example_hybrid hybrid_pipeline.cpp)
target_link_libraries(example_hybrid PRIVATE slotchain::slotchain)

add_executable(example_scoped scoped_disconnect.cpp)
target_link_libraries(example_scoped PRIVATE slotchain::slotchain)
