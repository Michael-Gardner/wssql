if(NOT ANTLR4CPP_FOUND)
	set(antlr4cpp_lib_name "antlr4-runtime")
	set(antlr4cpp_lib_path "/usr/local/lib")
	set(antlr4cpp_include_file "antlr4-runtime.h")
	set(antlr4cpp_include_path "/usr/local/include/antlr4-runtime")

	find_path(ANTLR4CPP_INCLUDE_DIRS
        NAMES ${antlr4cpp_include_file}
        PATHS ${antlr4cpp_include_path}
    ) 
	find_library(ANTLR4CPP_LIBRARIES
        NAMES ${antlr4cpp_lib_name}
        PATHS ${antlr4cpp_lib_path}
    )

	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(ANTLR4CPP DEFAULT_MSG
		ANTLR4CPP_LIBRARIES
		ANTLR4CPP_INCLUDE_DIRS
	)
	mark_as_advanced(ANTLR4CPP_INCLUDE_DIRS ANTLR4CPP_LIBRARIES)
endif()
