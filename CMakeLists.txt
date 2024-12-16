#----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.9)
project(LYSO)

#----------------------------------------------------------------------------

set(CMAKE_CXX_COMPILER g++)

#----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -fPIC -ffast-math -mavx")

#----------------------------------------------------------------------------

find_package(ROOT 6.30 CONFIG REQUIRED)

#----------------------------------------------------------------------------

find_package(OpenMP)

#----------------------------------------------------------------------------

set(CMAP_LIB_DIR "/home/yauhenitalochka/mnt/Files/Projects/CMAP")
set(CMAP_INCLUDE_DIR "/home/yauhenitalochka/mnt/Files/Projects/CMAP/include")

#----------------------------------------------------------------------------

find_library(CMAP_LIBS NAMES CMAP HINTS ${CMAP_LIB_DIR})

#----------------------------------------------------------------------------

include_directories(${PROJECT_SOURCE_DIR}/include
		                ${PROJECT_SOURCE_DIR}/shared/include
                    ${ROOT_INCLUDE_DIRS}
                    ${CMAP_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc
		              ${PROJECT_SOURCE_DIR}/shared/src/*.cc
                  ${PROJECT_SOURCE_DIR}/LYSO.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh
		              ${PROJECT_SOURCE_DIR}/shared/include/*.hh)

#----------------------------------------------------------------------------

separate_arguments(ROOT_EXE_LINKER_FLAGS)

#----------------------------------------------------------------------------

add_executable(LYSO ${sources} ${headers})
target_link_libraries(LYSO PUBLIC ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS} 
                      ROOT::Geom OpenMP::OpenMP_CXX ${CMAP_LIBS})

#----------------------------------------------------------------------------

set(LYSO_SCRIPTS run.param)

foreach(_script ${LYSO_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------

install(TARGETS LYSO DESTINATION ${PROJECT_SOURCE_DIR})

#----------------------------------------------------------------------------

add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)

#----------------------------------------------------------------------------