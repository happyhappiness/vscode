   int pid;
   int to_child_pipe[2];
   int from_child_pipe[2];
 
   if (pipe(to_child_pipe) < 0 ||
       pipe(from_child_pipe) < 0) {
-    fprintf(FERROR,"pipe: %s\n",strerror(errno));
+    rprintf(FERROR,"pipe: %s\n",strerror(errno));
     exit_cleanup(1);
   }
 
 
   pid = do_fork();
   if (pid < 0) {
-    fprintf(FERROR,"fork: %s\n",strerror(errno));
+    rprintf(FERROR,"fork: %s\n",strerror(errno));
     exit_cleanup(1);
   }
 
   if (pid == 0)
     {
       extern int orig_umask;
       if (dup2(to_child_pipe[0], STDIN_FILENO) < 0 ||
 	  close(to_child_pipe[1]) < 0 ||
 	  close(from_child_pipe[0]) < 0 ||
 	  dup2(from_child_pipe[1], STDOUT_FILENO) < 0) {
-	fprintf(FERROR,"Failed to dup/close : %s\n",strerror(errno));
+	rprintf(FERROR,"Failed to dup/close : %s\n",strerror(errno));
 	exit_cleanup(1);
       }
       if (to_child_pipe[0] != STDIN_FILENO) close(to_child_pipe[0]);
       if (from_child_pipe[1] != STDOUT_FILENO) close(from_child_pipe[1]);
       umask(orig_umask);
       execvp(command[0], command);
-      fprintf(FERROR,"Failed to exec %s : %s\n",
+      rprintf(FERROR,"Failed to exec %s : %s\n",
 	      command[0],strerror(errno));
       exit_cleanup(1);
     }
 
   if (close(from_child_pipe[1]) < 0 ||
       close(to_child_pipe[0]) < 0) {
-    fprintf(FERROR,"Failed to close : %s\n",strerror(errno));   
+    rprintf(FERROR,"Failed to close : %s\n",strerror(errno));   
     exit_cleanup(1);
   }
 
   *f_in = from_child_pipe[0];
   *f_out = to_child_pipe[1];
   
