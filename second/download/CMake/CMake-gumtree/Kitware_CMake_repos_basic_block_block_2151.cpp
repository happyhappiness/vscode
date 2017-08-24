{

#if defined(_WIN32)
  WIN32_FILE_ATTRIBUTE_DATA statSource;
  if (GetFileAttributesExW(Encoding::ToWindowsExtendedPath(source).c_str(),
                           GetFileExInfoStandard, &statSource) == 0) {
    return true;
  }

  WIN32_FILE_ATTRIBUTE_DATA statDestination;
  if (GetFileAttributesExW(
        Encoding::ToWindowsExtendedPath(destination).c_str(),
        GetFileExInfoStandard, &statDestination) == 0) {
    return true;
  }

  if (statSource.nFileSizeHigh != statDestination.nFileSizeHigh ||
      statSource.nFileSizeLow != statDestination.nFileSizeLow) {
    return true;
  }

  if (statSource.nFileSizeHigh == 0 && statSource.nFileSizeLow == 0) {
    return false;
  }
  off_t nleft =
    ((__int64)statSource.nFileSizeHigh << 32) + statSource.nFileSizeLow;

#else

  struct stat statSource;
  if (stat(source.c_str(), &statSource) != 0) {
    return true;
  }

  struct stat statDestination;
  if (stat(destination.c_str(), &statDestination) != 0) {
    return true;
  }

  if (statSource.st_size != statDestination.st_size) {
    return true;
  }

  if (statSource.st_size == 0) {
    return false;
  }
  off_t nleft = statSource.st_size;
#endif

#if defined(_WIN32)
  kwsys::ifstream finSource(source.c_str(), (std::ios::binary | std::ios::in));
  kwsys::ifstream finDestination(destination.c_str(),
                                 (std::ios::binary | std::ios::in));
#else
  kwsys::ifstream finSource(source.c_str());
  kwsys::ifstream finDestination(destination.c_str());
#endif
  if (!finSource || !finDestination) {
    return true;
  }

  // Compare the files a block at a time.
  char source_buf[KWSYS_ST_BUFFER];
  char dest_buf[KWSYS_ST_BUFFER];
  while (nleft > 0) {
    // Read a block from each file.
    std::streamsize nnext = (nleft > KWSYS_ST_BUFFER)
      ? KWSYS_ST_BUFFER
      : static_cast<std::streamsize>(nleft);
    finSource.read(source_buf, nnext);
    finDestination.read(dest_buf, nnext);

    // If either failed to read assume they are different.
    if (static_cast<std::streamsize>(finSource.gcount()) != nnext ||
        static_cast<std::streamsize>(finDestination.gcount()) != nnext) {
      return true;
    }

    // If this block differs the file differs.
    if (memcmp(static_cast<const void*>(source_buf),
               static_cast<const void*>(dest_buf),
               static_cast<size_t>(nnext)) != 0) {
      return true;
    }

    // Update the byte count remaining.
    nleft -= nnext;
  }

  // No differences found.
  return false;
}