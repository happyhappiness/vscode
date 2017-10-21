 
   if (f != -1) {
     send_file_entry(NULL,f);
     write_flush(f);
   }
 
-  if (verbose && recurse && !am_server)
+  if (verbose && recurse && !am_server && f != -1)
     fprintf(FINFO,"done\n");
 
   clean_flist(flist);
 
+  /* now send the uid/gid list. This was introduced in protocol version 15 */
+  if (f != -1 && remote_version >= 15) {
+	  send_uid_list(f);
+  }
+
   return flist;
 }
 
 
 struct file_list *recv_file_list(int f)
 {
