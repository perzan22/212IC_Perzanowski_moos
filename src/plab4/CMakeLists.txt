#--------------------------------------------------------
# The CMakeLists.txt for:                       plab4
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  lab4.cpp
  lab4_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(plab4 ${SRC})

TARGET_LINK_LIBRARIES(plab4
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)

