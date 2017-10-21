			args[ac++] = "--no-relative";
	}
	/* It's OK that this checks the upper-bound of the protocol_version. */
	if (relative_paths && !implied_dirs && (!am_sender || protocol_version >= 30))
		args[ac++] = "--no-implied-dirs";

	if (fuzzy_basis && am_sender)
		args[ac++] = "--fuzzy";

	if (remove_source_files == 1)
		args[ac++] = "--remove-source-files";
	else if (remove_source_files)
		args[ac++] = "--remove-sent-files";

	if (ac > MAX_SERVER_ARGS) { /* Not possible... */
		rprintf(FERROR, "argc overflow in server_options().\n");
		exit_cleanup(RERR_MALLOC);
	}

	*argc_p = ac;
	return;

    oom:
	out_of_memory("server_options");
}
