{
  if (path.empty()) {
    return false;
  }
#if defined(__CYGWIN__)
  // Convert path to native windows path if possible.
  char winpath[MAX_PATH];
  if (SystemTools::PathCygwinToWin32(path.c_str(), winpath)) {
    return (GetFileAttributesA(winpath) != INVALID_FILE_ATTRIBUTES);
  }
  struct stat st;
  return lstat(path.c_str(), &st) == 0;
#elif defined(_WIN32)
  return (GetFileAttributesW(Encoding::ToWindowsExtendedPath(path).c_str()) !=
          INVALID_FILE_ATTRIBUTES);
#else
  struct stat st;
  return lstat(path.c_str(), &st) == 0;
#endif
}