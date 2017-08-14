static int cmsys_shared_forward_to_real(int argc, char** argv_in)
{
  char const** argv = (char const**)argv_in;
  /* Get the directory containing this executable.  */
  char self_path[KWSYS_SHARED_FORWARD_MAXPATH];
  if (kwsys_shared_forward_self_path(argv[0], self_path)) {
    /* Found this executable.  Use it to get the library directory.  */
    char exe[KWSYS_SHARED_FORWARD_MAXPATH];
    if (kwsys_shared_forward_get_settings(self_path,
                                          kwsys_shared_forward_ldpath, exe)) {
      /* Append the old runtime search path.  */
      const char* old_ldpath = getenv(KWSYS_SHARED_FORWARD_LDPATH);
      if (old_ldpath) {
        strcat(kwsys_shared_forward_ldpath, kwsys_shared_forward_path_sep);
        strcat(kwsys_shared_forward_ldpath, old_ldpath);
      }

      /* Store the environment variable.  */
      putenv(kwsys_shared_forward_ldpath);

#if defined(KWSYS_SHARED_FORWARD_OPTION_COMMAND)
      /* Look for the command line replacement option.  */
      if (argc > 1 &&
          strcmp(argv[1], KWSYS_SHARED_FORWARD_OPTION_COMMAND) == 0) {
        if (argc > 2) {
          /* Use the command line given.  */
          strcpy(exe, argv[2]);
          argv += 2;
          argc -= 2;
        } else {
          /* The option was not given an executable.  */
          fprintf(stderr, "Option " KWSYS_SHARED_FORWARD_OPTION_COMMAND
                          " must be followed by a command line.\n");
          return 1;
        }
      }
#endif

#if defined(KWSYS_SHARED_FORWARD_OPTION_PRINT)
      /* Look for the print command line option.  */
      if (argc > 1 &&
          strcmp(argv[1], KWSYS_SHARED_FORWARD_OPTION_PRINT) == 0) {
        fprintf(stdout, "%s\n", kwsys_shared_forward_ldpath);
        fprintf(stdout, "%s\n", exe);
        return 0;
      }
#endif

#if defined(KWSYS_SHARED_FORWARD_OPTION_LDD)
      /* Look for the ldd command line option.  */
      if (argc > 1 && strcmp(argv[1], KWSYS_SHARED_FORWARD_OPTION_LDD) == 0) {
#if defined(KWSYS_SHARED_FORWARD_LDD)
        /* Use the named ldd-like executable and arguments.  */
        char const* ldd_argv[] = { KWSYS_SHARED_FORWARD_LDD, 0, 0 };
        ldd_argv[KWSYS_SHARED_FORWARD_LDD_N] = exe;
        kwsys_shared_forward_execvp(ldd_argv[0], ldd_argv);

        /* Report why execution failed.  */
        kwsys_shared_forward_print_failure(ldd_argv);
        return 1;
#else
        /* We have no ldd-like executable available on this platform.  */
        fprintf(stderr, "No ldd-like tool is known to this executable.\n");
        return 1;
#endif
      }
#endif

      /* Replace this process with the real executable.  */
      argv[0] = exe;
      kwsys_shared_forward_execvp(argv[0], argv);

      /* Report why execution failed.  */
      kwsys_shared_forward_print_failure(argv);
    } else {
      /* Could not convert self path to the library directory.  */
    }
  } else {
    /* Could not find this executable.  */
    fprintf(stderr, "Error locating executable \"%s\".\n", argv[0]);
  }

  /* Avoid unused argument warning.  */
  (void)argc;

  /* Exit with failure.  */
  return 1;
}