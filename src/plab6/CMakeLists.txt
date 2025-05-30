#--------------------------------------------------------
# The CMakeLists.txt for:                       plab6
# Author(s):                              
#--------------------------------------------------------

SET(SRC
  lab6.cpp
  lab6_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(plab6 ${SRC})

TARGET_LINK_LIBRARIES(plab6
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)

