{
    /* Running in install tree.  Use the install path and exe.  */
    search_path = search_path_install;
#if defined(_WIN32)
    exe_path = KWSYS_SHARED_FORWARD_EXE_INSTALL ".exe";
#else
    exe_path = KWSYS_SHARED_FORWARD_EXE_INSTALL;
#endif

#if defined(KWSYS_SHARED_FORWARD_CONFIG_NAME)
    /* Use the original self path directory.  */
    strcpy(self_path_logical, self_path);
#endif
  }