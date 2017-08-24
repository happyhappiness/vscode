{
  if (!SystemTools::PathExists(filename)) {
    if (create) {
      FILE* file = Fopen(filename, "a+b");
      if (file) {
        fclose(file);
        return true;
      }
      return false;
    } else {
      return true;
    }
  }
#if defined(_WIN32) && !defined(__CYGWIN__)
  HANDLE h = CreateFileW(Encoding::ToWindowsExtendedPath(filename).c_str(),
                         FILE_WRITE_ATTRIBUTES, FILE_SHARE_WRITE, 0,
                         OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
  if (!h) {
    return false;
  }
  FILETIME mtime;
  GetSystemTimeAsFileTime(&mtime);
  if (!SetFileTime(h, 0, 0, &mtime)) {
    CloseHandle(h);
    return false;
  }
  CloseHandle(h);
#elif KWSYS_CXX_HAS_UTIMENSAT
  struct timespec times[2] = { { 0, UTIME_OMIT }, { 0, UTIME_NOW } };
  if (utimensat(AT_FDCWD, filename.c_str(), times, 0) < 0) {
    return false;
  }
#else
  struct stat st;
  if (stat(filename.c_str(), &st) < 0) {
    return false;
  }
  struct timeval mtime;
  gettimeofday(&mtime, 0);
#if KWSYS_CXX_HAS_UTIMES
  struct timeval atime;
#if KWSYS_CXX_STAT_HAS_ST_MTIM
  atime.tv_sec = st.st_atim.tv_sec;
  atime.tv_usec = st.st_atim.tv_nsec / 1000;
#elif KWSYS_CXX_STAT_HAS_ST_MTIMESPEC
  atime.tv_sec = st.st_atimespec.tv_sec;
  atime.tv_usec = st.st_atimespec.tv_nsec / 1000;
#else
  atime.tv_sec = st.st_atime;
  atime.tv_usec = 0;
#endif
  struct timeval times[2] = { atime, mtime };
  if (utimes(filename.c_str(), times) < 0) {
    return false;
  }
#else
  struct utimbuf times = { st.st_atime, mtime.tv_sec };
  if (utime(filename.c_str(), &times) < 0) {
    return false;
  }
#endif
#endif
  return true;
}