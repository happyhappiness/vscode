      argv++;
    } else {
      sender = 1;

      p = strchr(argv[argc-1],':');
      if (!p) {
	local_server = 1;
      }

      if (local_server) {
	shell_machine = NULL;
	shell_path = argv[argc-1];
      } else {
	*p = 0;
	shell_machine = argv[argc-1];
	shell_path = p+1;
      }
      argc--;
    }

    if (shell_machine) {
      p = strchr(shell_machine,'@');
      if (p) {
	*p = 0;
	shell_user = shell_machine;
	shell_machine = p+1;
      }
    }

    if (verbose > 3) {
      fprintf(stderr,"cmd=%s machine=%s user=%s path=%s\n",
	      shell_cmd?shell_cmd:"",
	      shell_machine?shell_machine:"",
