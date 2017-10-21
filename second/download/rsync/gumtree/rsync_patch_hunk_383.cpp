   *f_in = from_child_pipe[0];
   *f_out = to_child_pipe[1];
   
   return pid;
 }
 
+int local_child(int argc, char **argv,int *f_in,int *f_out)
+{
+	int pid;
+	int to_child_pipe[2];
+	int from_child_pipe[2];
+
+	if (pipe(to_child_pipe) < 0 ||
+	    pipe(from_child_pipe) < 0) {
+		fprintf(FERROR,"pipe: %s\n",strerror(errno));
+		exit_cleanup(1);
+	}
+
+
+	pid = do_fork();
+	if (pid < 0) {
+		fprintf(FERROR,"fork: %s\n",strerror(errno));
+		exit_cleanup(1);
+	}
+
+	if (pid == 0) {
+		extern int am_sender;
+		extern int am_server;
+
+		am_sender = !am_sender;
+		am_server = 1;		
+
+		if (dup2(to_child_pipe[0], STDIN_FILENO) < 0 ||
+		    close(to_child_pipe[1]) < 0 ||
+		    close(from_child_pipe[0]) < 0 ||
+		    dup2(from_child_pipe[1], STDOUT_FILENO) < 0) {
+			fprintf(FERROR,"Failed to dup/close : %s\n",strerror(errno));
+			exit_cleanup(1);
+		}
+		if (to_child_pipe[0] != STDIN_FILENO) close(to_child_pipe[0]);
+		if (from_child_pipe[1] != STDOUT_FILENO) close(from_child_pipe[1]);
+		start_server(argc, argv);
+	}
+
+	if (close(from_child_pipe[1]) < 0 ||
+	    close(to_child_pipe[0]) < 0) {
+		fprintf(FERROR,"Failed to close : %s\n",strerror(errno));   
+		exit_cleanup(1);
+	}
+
+	*f_in = from_child_pipe[0];
+	*f_out = to_child_pipe[1];
+  
+	return pid;
+}
+
+
 
 void out_of_memory(char *str)
 {
-  fprintf(FERROR,"out of memory in %s\n",str);
+  fprintf(FERROR,"ERROR: out of memory in %s\n",str);
+  exit_cleanup(1);
+}
+
+void overflow(char *str)
+{
+  fprintf(FERROR,"ERROR: buffer overflow in %s\n",str);
   exit_cleanup(1);
 }
 
 
 
 int set_modtime(char *fname,time_t modtime)
