     setlinebuf(FINFO);
     setlinebuf(FERROR);
 #endif
 
     if (verbose > 3) 
       fprintf(FINFO,"parent=%d child=%d sender=%d recurse=%d\n",
-	      (int)getpid(),pid,sender,recurse);
+	      (int)getpid(),pid,am_sender,recurse);
 
-    if (sender) {
+    if (am_sender) {
       if (cvs_exclude)
 	add_cvs_excludes();
       if (delete_mode) 
 	send_exclude_list(f_out);
       flist = send_file_list(f_out,argc,argv);
       if (verbose > 3) 
