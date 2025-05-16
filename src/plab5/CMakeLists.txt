#--------------------------------------------------------
# The CMakeLists.txt for:                       plab5
# Author(s):                              
#--------------------------------------------------------

SET(SRC
  lab5.cpp
  lab5_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(plab5 ${SRC})

TARGET_LINK_LIBRARIES(plab5
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)

