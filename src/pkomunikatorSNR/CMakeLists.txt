#--------------------------------------------------------
# The CMakeLists.txt for:                       pkomunikatorSNR
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  komunikatorSNR.cpp
  komunikatorSNR_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pkomunikatorSNR ${SRC})

TARGET_LINK_LIBRARIES(pkomunikatorSNR
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

