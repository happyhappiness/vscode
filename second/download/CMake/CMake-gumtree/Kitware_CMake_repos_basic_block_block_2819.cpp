(i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-bad") == 0) {
      fprintf(stdout, "stdout from bad command line arg '-bad'\n");
      fprintf(stderr, "stderr from bad command line arg '-bad'\n");
      return 1;
    }
    if (argv[i][0] != '-') {
      fprintf(stdout, "%s:0:0: warning: message [checker]\n", argv[i]);
      break;
    }
  }