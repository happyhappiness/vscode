	    fprintf(FERROR,"ERROR: symbolic links not supported\n");
	    exit_cleanup(1);
    }
#endif

    if (am_server) {
	    start_server(argc, argv);
    }

    if (argc < 2) {
      usage(FERROR);
      exit_cleanup(1);
    }

    p = strchr(argv[0],':');

    if (p) {
      am_sender = 0;
      *p = 0;
      shell_machine = argv[0];
      shell_path = p+1;
      argc--;
      argv++;
    } else {
      am_sender = 1;

      p = strchr(argv[argc-1],':');
      if (!p) {
	local_server = 1;
      }

