 
     pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);
 
     write_int(f_out,PROTOCOL_VERSION);
     write_flush(f_out);
     {
-      int version = read_int(f_in);
-      if (version < MIN_PROTOCOL_VERSION) {
+      remote_version = read_int(f_in);
+      if (remote_version < MIN_PROTOCOL_VERSION) {
 	fprintf(stderr,"protocol version mismatch\n");
 	exit(1);
       }	
     }
 
+    setup_protocol();
+
     if (verbose > 3) 
       fprintf(stderr,"parent=%d child=%d sender=%d recurse=%d\n",
 	      (int)getpid(),pid,sender,recurse);
 
     if (sender) {
       if (cvs_exclude)
