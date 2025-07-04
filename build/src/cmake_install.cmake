# Install script for directory: /home/vboxuser/Desktop/moos-ivp-extend/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "None")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/lib_behaviors-test/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/pExampleApp/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/pXRelayTest/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/pkomunikator/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/pkomunikatorSNR/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/pkomunikatorTIME/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/plab2/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/plab2_1/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/plab3/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/plab4/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/plab5/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/plab6/cmake_install.cmake")
  include("/home/vboxuser/Desktop/moos-ivp-extend/build/src/psonarTask/cmake_install.cmake")

endif()

