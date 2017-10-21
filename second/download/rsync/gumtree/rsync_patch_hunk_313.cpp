   if (remote_version < MIN_PROTOCOL_VERSION ||
       remote_version > MAX_PROTOCOL_VERSION) {
     fprintf(FERROR,"protocol version mismatch - is your shell clean?\n");
     exit_cleanup(1);
   }	
 
-  if (remote_version == 10) {
-    send_file_entry = send_file_entry_v10;
-    receive_file_entry = receive_file_entry_v10;
-  } else {
-    send_file_entry = send_file_entry_v11;
-    receive_file_entry = receive_file_entry_v11;
-  }
+  if (verbose > 2)
+	  fprintf(FINFO, "local_version=%d remote_version=%d\n",
+		  PROTOCOL_VERSION, remote_version);
 
   if (remote_version >= 12) {
     if (am_server) {
       checksum_seed = time(NULL);
       write_int(f_out,checksum_seed);
     } else {
