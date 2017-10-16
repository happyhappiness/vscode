      break;
    case 'M': /* M for manual, huge help */
#ifdef USE_MANUAL
      hugehelp();
      return PARAM_HELP_REQUESTED;
#else
      fprintf(stderr,
              "curl: built-in manual was disabled at build-time!\n");
      return PARAM_OPTION_UNKNOWN;
#endif
    case 'n':
      switch(subletter) {
      case 'o': /* CA info PEM file */
        /* use .netrc or URL */
