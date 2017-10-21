			args[ac++] = "--no-relative";
	}
	/* It's OK that this checks the upper-bound of the protocol_version. */
	if (relative_paths && !implied_dirs && (!am_sender || protocol_version >= 30))
		args[ac++] = "--no-implied-dirs";

	if (remove_source_files == 1)
		args[ac++] = "--remove-source-files";
	else if (remove_source_files)
		args[ac++] = "--remove-sent-files";

	if (preallocate_files && am_sender)
		args[ac++] = "--preallocate";

	if (ac > MAX_SERVER_ARGS) { /* Not possible... */
		rprintf(FERROR, "argc overflow in server_options().\n");
		exit_cleanup(RERR_MALLOC);
	}

	if (remote_option_cnt) {
		int j;
		if (ac + remote_option_cnt > MAX_SERVER_ARGS) {
			rprintf(FERROR, "too many remote options specified.\n");
			exit_cleanup(RERR_SYNTAX);
		}
		for (j = 1; j <= remote_option_cnt; j++)
			args[ac++] = (char*)remote_options[j];
	}

	*argc_p = ac;
	return;

    oom:
	out_of_memory("server_options");
}
