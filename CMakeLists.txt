project (QCheck)

# this command finds Qt4 libraries and sets all required variables
find_package ( Qt4 REQUIRED )

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
include ( ${QT_USE_FILE} )

SET( SRCS
	main.cpp
	QCheck.cpp
	CheckSetup.cpp	
	)
	
#header files for moc
qt4_wrap_cpp ( MOC_SRCS
	QCheck.hpp
	CheckSetup.hpp
	)
  
# this will run uic on .ui files:
qt4_wrap_ui ( UI_HDRS
	./ui/QCheck.ui
	./ui/CheckSetup.ui
	)
  
# and finally an resource file
qt4_add_resources ( RC_SRCS
	)
	
include_directories (
	${PROJECT_SOURCE_DIR}
	${PROJECT_BINARY_DIR}
	)
	
add_executable(${PROJECT_NAME} 
	${MOC_SRCS} ${RC_SRCS} ${UI_HDRS} ${SRCS}
	)
	
#FIND_PACKAGE prepared QT_LIBRARIES variable for us:
target_link_libraries (${PROJECT_NAME} ${QT_LIBRARIES})
