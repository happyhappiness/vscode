{
#if defined(PATH_MAX)
    return PATH_MAX;
#else
#error "PATH_MAX undefined in the current platform"
#endif
  }