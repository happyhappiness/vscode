     }
 
     if (dry_run)
       verbose = MAX(verbose,1);
 
     if (am_server) {
-      int version = read_int(STDIN_FILENO);
-      if (version < MIN_PROTOCOL_VERSION) {
+      remote_version = read_int(STDIN_FILENO);
+      if (remote_version < MIN_PROTOCOL_VERSION) {
 	fprintf(stderr,"protocol version mismatch %d %d\n",
-		version,PROTOCOL_VERSION);
+		remote_version,PROTOCOL_VERSION);
 	exit(1);
       }
       write_int(STDOUT_FILENO,PROTOCOL_VERSION);
       write_flush(STDOUT_FILENO);
+
+      setup_protocol();
 	
       if (sender) {
 	recv_exclude_list(STDIN_FILENO);
 	if (cvs_exclude)
 	  add_cvs_excludes();
 	do_server_sender(argc,argv);
