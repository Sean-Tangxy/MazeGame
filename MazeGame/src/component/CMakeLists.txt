set(FREEGLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/freeglut/include")

add_library(
  component
  STATIC
  AudioManager.cpp
  Camera.cpp
  ItemManager.cpp
  SceneManagerGlobals.cpp
  Sprite.cpp
  UI.cpp
)

target_link_libraries(
  component
  SOIL
  freeglut
)

target_include_directories(
  component
  PUBLIC
  ${FREEGLUT_INCLUDE_DIR}
)