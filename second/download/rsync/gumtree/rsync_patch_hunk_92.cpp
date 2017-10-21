 
     if (dry_run)
       verbose = MAX(verbose,1);
 
     if (am_server) {
       int version = read_int(STDIN_FILENO);
-      if (version != PROTOCOL_VERSION) {
+      if (version < MIN_PROTOCOL_VERSION) {
 	fprintf(stderr,"protocol version mismatch %d %d\n",
 		version,PROTOCOL_VERSION);
 	exit(1);
       }
       write_int(STDOUT_FILENO,PROTOCOL_VERSION);
       write_flush(STDOUT_FILENO);
