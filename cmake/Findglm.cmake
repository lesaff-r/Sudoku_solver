#
# Find GLM
#
# Try to find GLM : OpenGL Mathematics.
# This module defines 
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
#
# The following variables can be set as arguments for the module.
# - GLM_ROOT_DIR : Root library directory of GLM 
#

# Additional modules
include(FindPackageHandleStandardArgs)

# Find include files
find_path( GLM_INCLUDE_DIR
	NAMES
		glm/glm.hpp
	HINTS
		"${GLM_LOCATION}/include"
		"$ENV{GLM_LOCATION}"
	PATHS
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		"$ENV{PROGRAMFILES}/glm/include"
	DOC
		"The directory where glm/glm.hpp resides")

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

# Define GLM_INCLUDE_DIRS
if (GLM_FOUND)
	set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLM_INCLUDE_DIR)