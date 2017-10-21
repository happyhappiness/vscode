			if (strcmp(cp, "rsh") == 0 || strcmp(cp, "remsh") == 0)
				blocking_io = 1;
		}

		server_options(args,&argc);

		if (argc >= MAX_ARGS - 2)
			goto arg_overflow;
	}

	args[argc++] = ".";

	if (!daemon_over_rsh) {
		while (remote_argc > 0) {
			if (argc >= MAX_ARGS - 1) {
			  arg_overflow:
				rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
				exit_cleanup(RERR_SYNTAX);
			}
			args[argc++] = *remote_argv++;
			remote_argc--;
		}
	}

	args[argc] = NULL;

	if (verbose > 3) {
		for (i = 0; i < argc; i++)
			rprintf(FCLIENT, "cmd[%d]=%s ", i, args[i]);
		rprintf(FCLIENT, "\n");
	}

	if (read_batch) {
		int from_gen_pipe[2];
		set_allow_inc_recurse();
		if (fd_pair(from_gen_pipe) < 0) {
			rsyserr(FERROR, errno, "pipe");
			exit_cleanup(RERR_IPC);
		}
		batch_gen_fd = from_gen_pipe[0];
		*f_out_p = from_gen_pipe[1];
		*f_in_p = batch_fd;
		ret = -1; /* no child pid */
#ifdef ICONV_CONST
		setup_iconv();
#endif
	} else if (local_server) {
		/* If the user didn't request --[no-]whole-file, force
		 * it on, but only if we're not batch processing. */
		if (whole_file < 0 && !write_batch)
			whole_file = 1;
		set_allow_inc_recurse();
		ret = local_child(argc, args, f_in_p, f_out_p, child_main);
#ifdef ICONV_CONST
		setup_iconv();
#endif
	} else {
#ifdef ICONV_CONST
		setup_iconv();
#endif
		if (protect_args) {
			int fd;
#ifdef ICONV_OPTION
			int convert = ic_send != (iconv_t)-1;
			xbuf outbuf, inbuf;

			if (convert)
				alloc_xbuf(&outbuf, 1024);
#endif

			ret = piped_child(args, f_in_p, f_out_p);

			for (i = 0; args[i]; i++) {} /* find first NULL */
			args[i] = "rsync"; /* set a new arg0 */
			if (verbose > 1)
				print_child_argv("protected args:", args + i + 1);
			fd = *f_out_p;
			do {
#ifdef ICONV_OPTION
				if (convert) {
					INIT_XBUF_STRLEN(inbuf, args[i]);
					iconvbufs(ic_send, &inbuf, &outbuf,
						  ICB_EXPAND_OUT | ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
					outbuf.buf[outbuf.len] = '\0';
					write_buf(fd, outbuf.buf, outbuf.len + 1);
					outbuf.len = 0;
				} else
#endif
					write_buf(fd, args[i], strlen(args[i]) + 1);
			} while (args[++i]);
			write_byte(fd, 0);
#ifdef ICONV_OPTION
			if (convert)
				free(outbuf.buf);
#endif
		} else
			ret = piped_child(args, f_in_p, f_out_p);
	}

	return ret;

  oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
