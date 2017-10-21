			if (strcmp(cp, "rsh") == 0 || strcmp(cp, "remsh") == 0)
				blocking_io = 1;
		}

		server_options(args,&argc);

		if (argc >= MAX_ARGS - 2) {
			rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
			exit_cleanup(RERR_SYNTAX);
		}
	}

	args[argc++] = ".";

	if (!daemon_over_rsh && path && *path)
		args[argc++] = path;

	args[argc] = NULL;

	if (verbose > 3) {
		for (i = 0; i < argc; i++)
			rprintf(FCLIENT, "cmd[%d]=%s ", i, args[i]);
		rprintf(FCLIENT, "\n");
	}

	if (read_batch) {
		int from_gen_pipe[2];
		if (fd_pair(from_gen_pipe) < 0) {
			rsyserr(FERROR, errno, "pipe");
			exit_cleanup(RERR_IPC);
		}
		batch_gen_fd = from_gen_pipe[0];
		*f_out = from_gen_pipe[1];
		*f_in = batch_fd;
		ret = -1; /* no child pid */
	} else if (local_server) {
		/* If the user didn't request --[no-]whole-file, force
		 * it on, but only if we're not batch processing. */
		if (whole_file < 0 && !write_batch)
			whole_file = 1;
		ret = local_child(argc, args, f_in, f_out, child_main);
	} else
		ret = piped_child(args,f_in,f_out);

	if (dir)
		free(dir);

	return ret;

  oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
