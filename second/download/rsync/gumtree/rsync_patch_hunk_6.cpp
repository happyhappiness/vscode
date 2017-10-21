 
     while (optind--) {
       argc--;
       argv++;
     }
 
+    if (dry_run)
+      verbose = MAX(verbose,1);
 
-    if (server) {
+    if (am_server) {
       int version = read_int(STDIN_FILENO);
       if (version != PROTOCOL_VERSION) {
 	fprintf(stderr,"protocol version mismatch %d %d\n",
 		version,PROTOCOL_VERSION);
 	exit(1);
       }
