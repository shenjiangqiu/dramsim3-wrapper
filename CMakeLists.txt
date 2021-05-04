add_subdirectory(DRAMsim3)
set(CMAKE_CXX_STANDARD 17)

add_library(dramsim3_wrapper SHARED dramsim3_wrapper.cc)
target_link_libraries(dramsim3_wrapper PUBLIC dramsim3)
target_include_directories(dramsim3_wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_test test.cc)
target_link_libraries(main_test PUBLIC dramsim3_wrapper)