     pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);
 
     write_int(f_out,PROTOCOL_VERSION);
     write_flush(f_out);
     {
       remote_version = read_int(f_in);
-      if (remote_version < MIN_PROTOCOL_VERSION) {
-	fprintf(stderr,"protocol version mismatch\n");
+      if (remote_version < MIN_PROTOCOL_VERSION ||
+	  remote_version > MAX_PROTOCOL_VERSION) {
+	fprintf(stderr,"protocol version mismatch - is your shell clean?\n");
 	exit(1);
       }	
     }
 
     setup_protocol();
 
