     signal(SIGHUP,SIGNAL_CAST sig_int);
 
     if (dry_run)
       verbose = MAX(verbose,1);
 
     if (am_server) {
-      remote_version = read_int(STDIN_FILENO);
-      if (remote_version < MIN_PROTOCOL_VERSION ||
-	  remote_version > MAX_PROTOCOL_VERSION) {
-	fprintf(stderr,"protocol version mismatch - is your shell clean?\n");
-	exit_cleanup(1);
-      }
-      write_int(STDOUT_FILENO,PROTOCOL_VERSION);
-      write_flush(STDOUT_FILENO);
-
-      setup_protocol();
+      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
 	
       if (sender) {
 	recv_exclude_list(STDIN_FILENO);
 	if (cvs_exclude)
 	  add_cvs_excludes();
 	do_server_sender(argc,argv);
