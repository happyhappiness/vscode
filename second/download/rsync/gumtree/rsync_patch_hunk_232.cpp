 
     if (sender) {
       if (cvs_exclude)
 	add_cvs_excludes();
       if (delete_mode) 
 	send_exclude_list(f_out);
-      flist = send_file_list(f_out,recurse,argc,argv);
+      flist = send_file_list(f_out,argc,argv);
       if (verbose > 3) 
 	fprintf(FERROR,"file list sent\n");
       send_files(flist,f_out,f_in);
       if (verbose > 3)
 	fprintf(FERROR,"waiting on %d\n",pid);
       waitpid(pid, &status, 0);
