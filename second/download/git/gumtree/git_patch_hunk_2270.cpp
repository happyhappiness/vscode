 	if (start_command(&child_process))
 		return error("cannot fork to run external filter %s", params->cmd);
 
 	sigchain_push(SIGPIPE, SIG_IGN);
 
 	if (params->src) {
-		write_err = (write_in_full(child_process.in, params->src, params->size) < 0);
+		write_err = (write_in_full(child_process.in,
+					   params->src, params->size) < 0);
+		if (errno == EPIPE)
+			write_err = 0;
 	} else {
 		write_err = copy_fd(params->fd, child_process.in);
+		if (write_err == COPY_WRITE_ERROR && errno == EPIPE)
+			write_err = 0;
 	}
 
 	if (close(child_process.in))
 		write_err = 1;
 	if (write_err)
 		error("cannot feed the input to external filter %s", params->cmd);
