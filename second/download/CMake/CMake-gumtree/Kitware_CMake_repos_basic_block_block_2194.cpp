{
#if defined(_WIN32) && !defined(__CYGWIN__)
    mode |= S_IWRITE;
#else
    mode |= S_IWUSR;
#endif
    SystemTools::SetPermissions(source, mode);
  }