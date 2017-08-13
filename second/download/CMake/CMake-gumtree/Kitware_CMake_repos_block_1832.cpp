{
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