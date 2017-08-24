{
  // Default to same time.
  *result = 0;
#if !defined(_WIN32) || defined(__CYGWIN__)
  // POSIX version.  Use stat function to get file modification time.
  struct stat s1;
  if (stat(f1.c_str(), &s1) != 0) {
    return false;
  }
  struct stat s2;
  if (stat(f2.c_str(), &s2) != 0) {
    return false;
  }
#if KWSYS_CXX_STAT_HAS_ST_MTIM
  // Compare using nanosecond resolution.
  if (s1.st_mtim.tv_sec < s2.st_mtim.tv_sec) {
    *result = -1;
  } else if (s1.st_mtim.tv_sec > s2.st_mtim.tv_sec) {
    *result = 1;
  } else if (s1.st_mtim.tv_nsec < s2.st_mtim.tv_nsec) {
    *result = -1;
  } else if (s1.st_mtim.tv_nsec > s2.st_mtim.tv_nsec) {
    *result = 1;
  }
#elif KWSYS_CXX_STAT_HAS_ST_MTIMESPEC
  // Compare using nanosecond resolution.
  if (s1.st_mtimespec.tv_sec < s2.st_mtimespec.tv_sec) {
    *result = -1;
  } else if (s1.st_mtimespec.tv_sec > s2.st_mtimespec.tv_sec) {
    *result = 1;
  } else if (s1.st_mtimespec.tv_nsec < s2.st_mtimespec.tv_nsec) {
    *result = -1;
  } else if (s1.st_mtimespec.tv_nsec > s2.st_mtimespec.tv_nsec) {
    *result = 1;
  }
#else
  // Compare using 1 second resolution.
  if (s1.st_mtime < s2.st_mtime) {
    *result = -1;
  } else if (s1.st_mtime > s2.st_mtime) {
    *result = 1;
  }
#endif
#else
  // Windows version.  Get the modification time from extended file attributes.
  WIN32_FILE_ATTRIBUTE_DATA f1d;
  WIN32_FILE_ATTRIBUTE_DATA f2d;
  if (!GetFileAttributesExW(Encoding::ToWindowsExtendedPath(f1).c_str(),
                            GetFileExInfoStandard, &f1d)) {
    return false;
  }
  if (!GetFileAttributesExW(Encoding::ToWindowsExtendedPath(f2).c_str(),
                            GetFileExInfoStandard, &f2d)) {
    return false;
  }

  // Compare the file times using resolution provided by system call.
  *result = (int)CompareFileTime(&f1d.ftLastWriteTime, &f2d.ftLastWriteTime);
#endif
  return true;
}