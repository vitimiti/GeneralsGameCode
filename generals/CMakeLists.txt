project(
  GENERALS
  LANGUAGES C CXX
  VERSION 0.1.0)

configure_file(${PROJECT_SOURCE_DIR}/src/generated.hpp.in
               ${PROJECT_BINARY_DIR}/generated/generated.hpp)

# Desktop only for now
find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME} WIN32)

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_include_directories(
  ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../common
                          ${PROJECT_BINARY_DIR}/generated)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if(WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME
                                                   CrossPlatform.Generals)

  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)
else()
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME
                                                   crossplat-generals)
endif()
