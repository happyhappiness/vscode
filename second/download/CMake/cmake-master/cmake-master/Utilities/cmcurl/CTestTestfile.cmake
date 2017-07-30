# CMake generated Testfile for 
# Source directory: /data/download/cmake/cmake-master/Utilities/cmcurl
# Build directory: /data/download/cmake/cmake-master/Utilities/cmcurl
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(curl "LIBCURL" "http://open.cdash.org/user.php")
subdirs("lib")
