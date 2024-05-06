#
# Try to find imgui library and include path.
# Once done this will define
#
# IMGUI_FOUND
# IMGUI_INCLUDE_DIR
# 

# Additional modules
include(FindPackageHandleStandardArgs)

FIND_PATH(IMGUI_INCLUDE_DIR
    NAMES
        imgui.h
    PATHS
		${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
		/usr/local
		/usr
    DOC
        "The directory where imgui/imgui.h resides"
)

find_package_handle_standard_args(IMGUI REQUIRED_VARS IMGUI_INCLUDE_DIR)

if (IMGUI_FOUND)
	set(IMGUI_INCLUDE_PATH ${IMGUI_INCLUDE_DIR})
endif()

mark_as_advanced(IMGUI_INCLUDE_DIR)