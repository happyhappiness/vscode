{
#if defined(_WIN32)
  DWORD attr =
    GetFileAttributesW(Encoding::ToWindowsExtendedPath(file).c_str());
  if (attr == INVALID_FILE_ATTRIBUTES) {
    return false;
  }
  if ((attr & FILE_ATTRIBUTE_READONLY) != 0) {
    mode = (_S_IREAD | (_S_IREAD >> 3) | (_S_IREAD >> 6));
  } else {
    mode = (_S_IWRITE | (_S_IWRITE >> 3) | (_S_IWRITE >> 6)) |
      (_S_IREAD | (_S_IREAD >> 3) | (_S_IREAD >> 6));
  }
  if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0) {
    mode |= S_IFDIR | (_S_IEXEC | (_S_IEXEC >> 3) | (_S_IEXEC >> 6));
  } else {
    mode |= S_IFREG;
  }
  size_t dotPos = file.rfind('.');
  const char* ext = dotPos == std::string::npos ? 0 : (file.c_str() + dotPos);
  if (ext && (Strucmp(ext, ".exe") == 0 || Strucmp(ext, ".com") == 0 ||
              Strucmp(ext, ".cmd") == 0 || Strucmp(ext, ".bat") == 0)) {
    mode |= (_S_IEXEC | (_S_IEXEC >> 3) | (_S_IEXEC >> 6));
  }
#else
  struct stat st;
  if (stat(file.c_str(), &st) < 0) {
    return false;
  }
  mode = st.st_mode;
#endif
  return true;
}