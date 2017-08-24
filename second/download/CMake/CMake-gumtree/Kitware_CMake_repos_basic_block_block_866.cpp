{
  /* Possible search paths.  */
  static const char* search_path_build[] = { KWSYS_SHARED_FORWARD_PATH_BUILD,
                                             0 };
  static const char* search_path_install[] = {
    KWSYS_SHARED_FORWARD_PATH_INSTALL, 0
  };

  /* Chosen paths.  */
  const char** search_path;
  const char* exe_path;

/* Get the real name of the build and self paths.  */
#if defined(KWSYS_SHARED_FORWARD_CONFIG_NAME)
  char build_path[] =
    KWSYS_SHARED_FORWARD_DIR_BUILD "/" KWSYS_SHARED_FORWARD_CONFIG_NAME;
  char self_path_logical[KWSYS_SHARED_FORWARD_MAXPATH];
#else
  char build_path[] = KWSYS_SHARED_FORWARD_DIR_BUILD;
  const char* self_path_logical = self_path;
#endif
  char build_path_real[KWSYS_SHARED_FORWARD_MAXPATH];
  char self_path_real[KWSYS_SHARED_FORWARD_MAXPATH];
  if (!kwsys_shared_forward_realpath(self_path, self_path_real)) {
    char msgbuf[KWSYS_SHARED_FORWARD_MAXPATH];
    kwsys_shared_forward_strerror(msgbuf);
    fprintf(stderr, "Error converting self path \"%s\" to real path: %s\n",
            self_path, msgbuf);
    return 0;
  }

  /* Check whether we are running in the build tree or an install tree.  */
  if (kwsys_shared_forward_realpath(build_path, build_path_real) &&
      kwsys_shared_forward_samepath(self_path_real, build_path_real)) {
    /* Running in build tree.  Use the build path and exe.  */
    search_path = search_path_build;
#if defined(_WIN32)
    exe_path = KWSYS_SHARED_FORWARD_EXE_BUILD ".exe";
#else
    exe_path = KWSYS_SHARED_FORWARD_EXE_BUILD;
#endif

#if defined(KWSYS_SHARED_FORWARD_CONFIG_NAME)
    /* Remove the configuration directory from self_path.  */
    kwsys_shared_forward_dirname(self_path, self_path_logical);
#endif
  } else {
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

  /* Construct the runtime search path.  */
  {
    const char** dir;
    for (dir = search_path; *dir; ++dir) {
      /* Add separator between path components.  */
      if (dir != search_path) {
        strcat(ldpath, kwsys_shared_forward_path_sep);
      }

      /* Add this path component.  */
      if (!kwsys_shared_forward_fullpath(self_path_logical, *dir,
                                         ldpath + strlen(ldpath),
                                         "runtime path entry")) {
        return 0;
      }
    }
  }

  /* Construct the executable location.  */
  if (!kwsys_shared_forward_fullpath(self_path_logical, exe_path, exe,
                                     "executable file")) {
    return 0;
  }
  return 1;
}