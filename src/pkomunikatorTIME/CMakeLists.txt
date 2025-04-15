#--------------------------------------------------------
# The CMakeLists.txt for:                       pkomunikatorTIME
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  komunikatorTIME.cpp
  komunikatorTIME_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pkomunikatorTIME ${SRC})

TARGET_LINK_LIBRARIES(pkomunikatorTIME
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

