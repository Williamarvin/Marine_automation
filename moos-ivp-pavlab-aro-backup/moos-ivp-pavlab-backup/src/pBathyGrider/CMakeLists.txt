#--------------------------------------------------------
# The CMakeLists.txt for:                       pBathyGrider
# Author(s):                              
#--------------------------------------------------------


# Armadillo linking taken from Blake
#########################################################################
# enable C++11 (see top-level CMakeLists.txt for macro definition)
use_cxx11()

# add compiler flags to optimize Armadillo build
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -DARMA_DONT_USE_WRAPPER")

# link linear algebra libraries
# (1) check to see if OpenBLAS is installed
# (2) if not, and APPLE=TRUE use Accelerate Framework.
# (3) if not, and APPLE=FALSE use generic BLAS and LAPACK.
set(BLA_VENDOR OpenBLAS)
find_package(BLAS)
if(${BLAS_FOUND})
  set (OPENBLAS_FOUND TRUE)
endif()

if(OPENBLAS_FOUND)
  message(STATUS "Compiling Armadillo using OpenBLAS.")
else()
  if(UNIX AND APPLE)
    message(STATUS "Compiling Armadillo using Apple Accelerate Framework.")
    find_library(ACCELERATE_FRAMEWORK Accelerate)
  elseif(UNIX AND NOT APPLE)
    set(BLA_VENDOR)
    find_package(BLAS)
    find_package(LAPACK)
    if(${BLAS_FOUND} AND ${LAPACK_FOUND})
      set (BLAS_AND_LAPACK_FOUND TRUE)
    endif()
    if(BLAS_AND_LAPACK_FOUND)
      message(STATUS "Compiling Armadillo using generic BLAS and LAPACK.")
      message(STATUS "BLAS VENDOR:    " ${BLA_VENDOR})
      message(STATUS "BLAS LIBRARIES: " ${BLAS_LIBRARIES})
    else()
      message(FATAL_ERROR "ERROR: BLAS or LAPACK not found.")
    endif()
  else()
    message(FATAL_ERROR "ERROR: Only Linux and MacOS supported.")
  endif()
endif()



find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})  # Also taken from Blake.

SET(SRC
  BathyGrider.cpp
  BathyGrider_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pBathyGrider ${SRC})

TARGET_LINK_LIBRARIES(pBathyGrider
  ${MOOS_LIBRARIES}
  ${ARMADILLO_LIBRARIES}
   MOOSGeodesy
   geometry
   apputil
   mbutil
   m
   pthread
   bathygrid
   learning
)

 # link the appropriate linear algebra libraries  # Also taken from Blake
if(OPENBLAS_FOUND OR ((UNIX AND NOT APPLE) AND BLAS_AND_LAPACK_FOUND))
  TARGET_LINK_LIBRARIES(pBathyGrider
    ${BLAS_LIBRARIES}
    ${LAPACK_LIBRARIES})
else()
  TARGET_LINK_LIBRARIES(pBathyGrider
    ${ACCELERATE_FRAMEWORK})
endif()
