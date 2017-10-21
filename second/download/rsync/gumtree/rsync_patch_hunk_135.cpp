   }
 }
 
 
 
 
-void setup_protocol(void)
+void setup_protocol(int f_out,int f_in)
 {
+  if (am_server) {
+    remote_version = read_int(f_in);
+    write_int(f_out,PROTOCOL_VERSION);
+    write_flush(f_out);
+  } else {
+    write_int(f_out,PROTOCOL_VERSION);
+    write_flush(f_out);
+    remote_version = read_int(f_in);
+  }
+
+  if (remote_version < MIN_PROTOCOL_VERSION ||
+      remote_version > MAX_PROTOCOL_VERSION) {
+    fprintf(FERROR,"protocol version mismatch - is your shell clean?\n");
+    exit_cleanup(1);
+  }	
+
   if (remote_version == 10) {
     send_file_entry = send_file_entry_v10;
     receive_file_entry = receive_file_entry_v10;
   } else {
     send_file_entry = send_file_entry_v11;
     receive_file_entry = receive_file_entry_v11;
   }
+
+  if (remote_version >= 12) {
+    if (am_server) {
+      checksum_seed = time(NULL);
+      write_int(f_out,checksum_seed);
+    } else {
+      checksum_seed = read_int(f_in);
+    }
+  }
 }
 
