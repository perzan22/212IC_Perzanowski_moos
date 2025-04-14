#--------------------------------------------------------
# The CMakeLists.txt for:                       plab2
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  lab2.cpp
  lab2_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(plab2 ${SRC})

TARGET_LINK_LIBRARIES(plab2
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)
   
   

