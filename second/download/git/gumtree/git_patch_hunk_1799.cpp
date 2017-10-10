 	/* expand all %f with the quoted path */
 	strbuf_expand(&cmd, params->cmd, strbuf_expand_dict_cb, &dict);
 	strbuf_release(&path);
 
 	argv[0] = cmd.buf;
 
-	memset(&child_process, 0, sizeof(child_process));
 	child_process.argv = argv;
 	child_process.use_shell = 1;
 	child_process.in = -1;
 	child_process.out = out;
 
 	if (start_command(&child_process))
 		return error("cannot fork to run external filter %s", params->cmd);
 
 	sigchain_push(SIGPIPE, SIG_IGN);
 
-	write_err = (write_in_full(child_process.in, params->src, params->size) < 0);
+	if (params->src) {
+		write_err = (write_in_full(child_process.in, params->src, params->size) < 0);
+	} else {
+		write_err = copy_fd(params->fd, child_process.in);
+	}
+
 	if (close(child_process.in))
 		write_err = 1;
 	if (write_err)
 		error("cannot feed the input to external filter %s", params->cmd);
 
 	sigchain_pop(SIGPIPE);
