{
#if defined(MAXPATHLEN)
    cp->RealWorkingDirectoryLength = MAXPATHLEN;
#elif defined(PATH_MAX)
    cp->RealWorkingDirectoryLength = PATH_MAX;
#else
    cp->RealWorkingDirectoryLength = 4096;
#endif
    cp->RealWorkingDirectory =
      (char*)malloc((size_t)(cp->RealWorkingDirectoryLength));
    if (!cp->RealWorkingDirectory) {
      return 0;
    }
  }