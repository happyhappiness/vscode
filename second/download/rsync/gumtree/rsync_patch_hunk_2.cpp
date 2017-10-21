 
     if (verbose > 3) 
       fprintf(stderr,"parent=%d child=%d sender=%d recurse=%d\n",
 	      (int)getpid(),pid,sender,recurse);
 
     if (sender) {
+      if (cvs_exclude)
+	add_cvs_excludes();
       flist = send_file_list(f_out,recurse,argc,argv);
       if (verbose > 3) 
 	fprintf(stderr,"file list sent\n");
       send_files(flist,f_out,f_in);
       if (verbose > 3)
 	fprintf(stderr,"waiting on %d\n",pid);
       waitpid(pid, &status, 0);
       report(-1);
       exit(status);
     }
 
+    send_exclude_list(f_out);
+
     flist = recv_file_list(f_in);
     if (flist->count == 0) {
       exit(0);
     }
 
     {
