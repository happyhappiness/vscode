if(NOT "/data/download/cmake/cmake-master/Tests/CMakeTests" MATCHES "^/")
  set(slash /)
endif()
set(url "file://${slash}/data/download/cmake/cmake-master/Tests/CMakeTests/FileDownloadInput.png")
set(dir "/data/download/cmake/cmake-master/Tests/CMakeTests/downloads")

file(DOWNLOAD
  ${url}
  ${dir}/file3.png
  TIMEOUT 2
  STATUS status
  EXPECTED_HASH SHA1=5555555555555555555555555555555555555555
  )
