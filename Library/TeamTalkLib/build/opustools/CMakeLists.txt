project(OPUSTools)

include(ExternalProject)

##################################################
# OPUS Tools
##################################################
if (TOOLCHAIN_OGG)
  ExternalProject_Add(opustools-src
    GIT_REPOSITORY    https://github.com/xiph/opus-tools
    GIT_TAG           v0.1.10
    UPDATE_COMMAND    ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    DEPENDS           ogg
    BUILD_BYPRODUCTS  <SOURCE_DIR>/src/opus_header.c <SOURCE_DIR>/src/opus_header.h
    )
else()
  ExternalProject_Add(opustools-src
    GIT_REPOSITORY    https://github.com/xiph/opus-tools.git
    GIT_TAG           v0.1.10
    UPDATE_COMMAND    ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    BUILD_BYPRODUCTS  <SOURCE_DIR>/src/opus_header.c <SOURCE_DIR>/src/opus_header.h
    )
endif()

ExternalProject_Get_Property(opustools-src SOURCE_DIR)
file(MAKE_DIRECTORY ${SOURCE_DIR}/src)

add_library(opustools STATIC ${SOURCE_DIR}/src/opus_header.h ${SOURCE_DIR}/src/opus_header.c)
set_property(TARGET opustools PROPERTY OUTPUT_NAME_DEBUG opustoolsd)
add_dependencies(opustools opustools-src)
target_link_libraries(opustools ogg)
target_include_directories (opustools INTERFACE ${SOURCE_DIR}/src)
