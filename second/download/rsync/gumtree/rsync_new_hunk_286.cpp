    signal(SIGPIPE,SIGNAL_CAST sig_int);
    signal(SIGHUP,SIGNAL_CAST sig_int);

    if (dry_run)
      verbose = MAX(verbose,1);

#ifndef SUPPORT_LINKS
    if (!am_server && preserve_links) {
	    fprintf(FERROR,"ERROR: symbolic links not supported\n");
	    exit_cleanup(1);
    }
#endif

    if (am_server) {
      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
	
      if (sender) {
	recv_exclude_list(STDIN_FILENO);
	if (cvs_exclude)
