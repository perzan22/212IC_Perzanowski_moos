#--------------------------------------------------------
# The CMakeLists.txt for:                       plab3
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  lab3.cpp
  lab3_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(plab3 ${SRC})

TARGET_LINK_LIBRARIES(plab3
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)

