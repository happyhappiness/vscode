# Install script for directory: /data/download/cmake/cmake-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/cmake-3.8" TYPE FILE FILES "/data/download/cmake/cmake-master/Copyright.txt")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake-3.8" TYPE DIRECTORY PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ DIR_PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "/data/download/cmake/cmake-master/Help"
    "/data/download/cmake/cmake-master/Modules"
    "/data/download/cmake/cmake-master/Templates"
    REGEX "/[^/]*\\.sh[^/]*$" PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE REGEX "Help/dev($|/)" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/data/download/cmake/cmake-master/Source/kwsys/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/KWIML/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmlibrhash/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmzlib/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmcurl/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmcompress/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmexpat/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmbzip2/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmliblzma/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmlibarchive/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmjsoncpp/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmlibuv/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Source/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Utilities/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Tests/cmake_install.cmake")
  include("/data/download/cmake/cmake-master/Auxiliary/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/data/download/cmake/cmake-master/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
