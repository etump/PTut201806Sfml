cmake_minimum_required(VERSION 2.8)


message("${SFML_ROOT}")
PROJECT (exemple1)

find_package(SFML 2 REQUIRED network audio graphics window system)


file(GLOB exemple1_SRCS
    "*.h"
    "*.cpp")

ADD_EXECUTABLE (exemple1 ${exemple1_SRCS})



# If found, include and link; otherwise output error message
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries( exemple1 sfml-network sfml-window sfml-audio sfml-graphics sfml-system)
else()
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()