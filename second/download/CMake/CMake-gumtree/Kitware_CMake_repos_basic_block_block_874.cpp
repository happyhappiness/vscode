(argc > 2) {
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