#--------------------------------------------------------
# The CMakeLists.txt for:                       pkomunikator
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  komunikator.cpp
  komunikator_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pkomunikator ${SRC})

TARGET_LINK_LIBRARIES(pkomunikator
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

