    signal(SIGHUP,SIGNAL_CAST sig_int);

    if (dry_run)
      verbose = MAX(verbose,1);

    if (am_server) {
      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
	
      if (sender) {
	recv_exclude_list(STDIN_FILENO);
	if (cvs_exclude)
	  add_cvs_excludes();
	do_server_sender(argc,argv);
