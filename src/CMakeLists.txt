##############################################################################
# FILE:        moos-ivp-extend/src/CMakeLists.txt
# DATE:        2010/09/07
#              2020/05/09 minor mods
# DESCRIPTION: CMakeLists.txt file for the moos-ivp-extend source directory
##############################################################################


#============================================================================
# Add the libraries in the current directory to the include path
#============================================================================
FILE(GLOB LOCAL_LIBRARY_DIRS ./lib_*)
INCLUDE_DIRECTORIES(${LOCAL_LIBRARY_DIRS})

#============================================================================
# List the subdirectories to build...
#============================================================================
ADD_SUBDIRECTORY(lib_behaviors-test)
ADD_SUBDIRECTORY(pExampleApp)
ADD_SUBDIRECTORY(pXRelayTest)
ADD_SUBDIRECTORY(pkomunikator)
ADD_SUBDIRECTORY(pkomunikatorSNR)
ADD_SUBDIRECTORY(pkomunikatorTIME)
ADD_SUBDIRECTORY(plab2)
ADD_SUBDIRECTORY(plab2_1)
ADD_SUBDIRECTORY(plab3)
ADD_SUBDIRECTORY(plab4)
ADD_SUBDIRECTORY(plab5)
ADD_SUBDIRECTORY(plab6)
ADD_SUBDIRECTORY(psonarTask)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################