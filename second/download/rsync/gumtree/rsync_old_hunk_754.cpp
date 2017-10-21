				cp = cmd;
			if (strcmp(cp, "rsh") == 0 || strcmp(cp, "remsh") == 0)
				blocking_io = 1;
		}

		server_options(args,&argc);
	}

	args[argc++] = ".";

	if (!daemon_over_rsh && path && *path)
		args[argc++] = path;

	if (argc >= (int)(sizeof args / sizeof args[0])) {
		rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
		exit_cleanup(RERR_MALLOC); /* XXX Need better RERR? */
	}

	args[argc] = NULL;

	if (verbose > 3) {
		rprintf(FINFO,"cmd=");
		for (i=0;i<argc;i++)
			rprintf(FINFO,"%s ",args[i]);
		rprintf(FINFO,"\n");
	}

	if (local_server) {
		if (read_batch)
			create_flist_from_batch(); /* sets batch_flist */
		ret = local_child(argc, args, f_in, f_out, child_main);
	} else {
		ret = piped_child(args,f_in,f_out);
	}

	if (dir) free(dir);

	return ret;

oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
