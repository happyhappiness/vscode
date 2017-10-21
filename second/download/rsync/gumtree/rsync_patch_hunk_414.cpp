       tv.tv_sec = BLOCKING_TIMEOUT;
       tv.tv_usec = 0;
       count = select(fd_count,buffer_f_in == -1? NULL: &r_fds,
 		     &w_fds,NULL,&tv);
       if (count == -1 && errno != EINTR) {
 	      if (verbose > 1) 
-		      fprintf(FERROR,"select error: %s\n", strerror(errno));
+		      rprintf(FERROR,"select error: %s\n", strerror(errno));
 	      exit_cleanup(1);
       }
 
       if (count == 0) {
 	      check_timeout();
 	      continue;
