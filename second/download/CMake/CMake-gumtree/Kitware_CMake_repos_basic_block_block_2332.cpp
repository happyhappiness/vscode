{
#if defined(_WIN32) || defined(__CYGWIN__)
  // On Windows, the name must be at least two characters long.
  if (len < 2) {
    return false;
  }
  if (in_name[1] == ':') {
    return true;
  }
  if (in_name[0] == '\\') {
    return true;
  }
#else
  // On UNIX, the name must be at least one character long.
  if (len < 1) {
    return false;
  }
#endif
#if !defined(_WIN32)
  if (in_name[0] == '~') {
    return true;
  }
#endif
  // On UNIX, the name must begin in a '/'.
  // On Windows, if the name begins in a '/', then it is a full
  // network path.
  if (in_name[0] == '/') {
    return true;
  }
  return false;
}