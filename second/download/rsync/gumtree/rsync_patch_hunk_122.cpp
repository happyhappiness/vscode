   }
 
   if ((pid=fork()) == 0) {
     recv_files(STDIN_FILENO,flist,local_name);
     if (verbose > 2)
       fprintf(stderr,"receiver read %d\n",read_total());
-    exit(0);
+    exit_cleanup(0);
   }
 
   generate_files(STDOUT_FILENO,flist,local_name);
 
   waitpid(pid, &status, 0);
-  exit(status);
+  exit_cleanup(status);
 }
 
 
 static void usage(FILE *f)
 {
   fprintf(f,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",
