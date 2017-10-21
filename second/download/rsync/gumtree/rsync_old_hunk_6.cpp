
    while (optind--) {
      argc--;
      argv++;
    }


    if (server) {
      int version = read_int(STDIN_FILENO);
      if (version != PROTOCOL_VERSION) {
	fprintf(stderr,"protocol version mismatch %d %d\n",
		version,PROTOCOL_VERSION);
	exit(1);
      }
