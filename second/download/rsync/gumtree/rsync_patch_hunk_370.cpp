 
   status = do_recv(STDIN_FILENO,STDOUT_FILENO,flist,local_name);
   exit_cleanup(status);
 }
 
 
+void start_server(int argc, char *argv[])
+{
+      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
+	
+      if (am_sender) {
+	      recv_exclude_list(STDIN_FILENO);
+	      if (cvs_exclude)
+		      add_cvs_excludes();
+	      do_server_sender(argc,argv);
+      } else {
+	      do_server_recv(argc,argv);
+      }
+      exit_cleanup(0);
+}
+
+
 static void usage(FILE *f)
 {
   fprintf(f,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",
 	  VERSION);
   fprintf(f,"Usage:\t%s [options] src user@host:dest\nOR",RSYNC_NAME);
   fprintf(f,"\t%s [options] user@host:src dest\n\n",RSYNC_NAME);
