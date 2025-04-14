#--------------------------------------------------------
# The CMakeLists.txt for:                       plab2_1
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  lab2_1.cpp
  lab2_1_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(plab2_1 ${SRC})

TARGET_LINK_LIBRARIES(plab2_1
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)

