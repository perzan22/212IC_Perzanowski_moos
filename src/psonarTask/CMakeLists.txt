#--------------------------------------------------------
# The CMakeLists.txt for:                       psonarTask
# Author(s):                              Olaf Perzanowski
#--------------------------------------------------------

SET(SRC
  sonarTask.cpp
  sonarTask_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(psonarTask ${SRC})

TARGET_LINK_LIBRARIES(psonarTask
   ${MOOS_LIBRARIES}
   apputil
   geometry
   mbutil
   m
   pthread)

