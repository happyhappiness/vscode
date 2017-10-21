 	fprintf(stderr,"file list sent\n");
       send_files(flist,f_out,f_in);
       if (verbose > 3)
 	fprintf(stderr,"waiting on %d\n",pid);
       waitpid(pid, &status, 0);
       report(-1);
-      exit(status);
+      exit_cleanup(status);
     }
 
     send_exclude_list(f_out);
 
     flist = recv_file_list(f_in);
     if (!flist || flist->count == 0) {
       fprintf(stderr,"nothing to do\n");
-      exit(0);
+      exit_cleanup(0);
     }
 
     local_name = get_local_name(flist,argv[0]);
 
     if ((pid2=fork()) == 0) {
       recv_files(f_in,flist,local_name);
       if (verbose > 1)
 	fprintf(stderr,"receiver read %d\n",read_total());
-      exit(0);
+      exit_cleanup(0);
     }
 
     generate_files(f_out,flist,local_name);
 
     waitpid(pid2, &status2, 0);
 
