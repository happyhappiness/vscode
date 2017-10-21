 		am_server = 1;		
 
 		if (dup2(to_child_pipe[0], STDIN_FILENO) < 0 ||
 		    close(to_child_pipe[1]) < 0 ||
 		    close(from_child_pipe[0]) < 0 ||
 		    dup2(from_child_pipe[1], STDOUT_FILENO) < 0) {
-			fprintf(FERROR,"Failed to dup/close : %s\n",strerror(errno));
+			rprintf(FERROR,"Failed to dup/close : %s\n",strerror(errno));
 			exit_cleanup(1);
 		}
 		if (to_child_pipe[0] != STDIN_FILENO) close(to_child_pipe[0]);
 		if (from_child_pipe[1] != STDOUT_FILENO) close(from_child_pipe[1]);
-		start_server(argc, argv);
+		start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
 	}
 
 	if (close(from_child_pipe[1]) < 0 ||
 	    close(to_child_pipe[0]) < 0) {
-		fprintf(FERROR,"Failed to close : %s\n",strerror(errno));   
+		rprintf(FERROR,"Failed to close : %s\n",strerror(errno));   
 		exit_cleanup(1);
 	}
 
 	*f_in = from_child_pipe[0];
 	*f_out = to_child_pipe[1];
   
