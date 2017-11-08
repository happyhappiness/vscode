int parse_arguments(int *argc, const char ***argv, int frommain)
{
	int opt;
	char *ref = lp_refuse_options(module_id);
        poptContext pc;

        /* TODO: Call poptReadDefaultConfig; handle errors. */

        /* The context leaks in case of an error, but if there's a
         * problem we always exit anyhow. */
        pc = poptGetContext(RSYNC_NAME, *argc, *argv, long_options, 0);

	while ((opt = poptGetNextOpt(pc)) != -1) {
		if (ref) {
			if (check_refuse_options(ref, opt)) return 0;
		}

                /* most options are handled automatically by popt;
                 * only special cases are returned and listed here. */

		switch (opt) {
		case OPT_VERSION:
                        print_rsync_version(FINFO);
			exit_cleanup(0);
			
		case OPT_MODIFY_WINDOW:
                        /* The value has already been set by popt, but
                         * we need to remember that we're using a
                         * non-default setting. */
			modify_window_set = 1;
			break;
			
		case OPT_DELETE_EXCLUDED:
			delete_excluded = 1;
			delete_mode = 1;
			break;

		case OPT_EXCLUDE:
			add_exclude(poptGetOptArg(pc), 0);
			break;

		case OPT_INCLUDE:
			add_exclude(poptGetOptArg(pc), 1);
			break;

		case OPT_EXCLUDE_FROM:
			add_exclude_file(poptGetOptArg(pc), 1, 0);
			break;

		case OPT_INCLUDE_FROM:
			add_exclude_file(poptGetOptArg(pc), 1, 1);
			break;

		case OPT_WHOLE_FILE:
			whole_file = 1;
			no_whole_file = 0;
			break;

		case OPT_NO_WHOLE_FILE:
			no_whole_file = 1;
			whole_file = 0;
			break;

		case OPT_NO_BLOCKING_IO:
			blocking_io = 0;
			break;

		case 'h':
			usage(FINFO);
			exit_cleanup(0);

		case 'H':
#if SUPPORT_HARD_LINKS
			preserve_hard_links=1;
#else
                        /* FIXME: Don't say "server" if this is
                         * happening on the client. */
                        /* FIXME: Why do we have the duplicated
                         * rprintf?  Everybody who gets this message
                         * ought to send it to the client and also to
                         * the logs. */
			snprintf(err_buf,sizeof(err_buf),
                                 "hard links are not supported on this %s\n",
				 am_server ? "server" : "client");
			rprintf(FERROR,"ERROR: hard links not supported on this platform\n");
			return 0;
#endif /* SUPPORT_HARD_LINKS */
			break;

		case 'v':
			verbose++;
			break;

		case 'q':
			if (frommain) quiet++;
			break;

		case 'a':
			recurse=1;
#if SUPPORT_LINKS
			preserve_links=1;
#endif
			preserve_perms=1;
			preserve_times=1;
			preserve_gid=1;
			preserve_uid=1;
			preserve_devices=1;
			break;

		case OPT_SENDER:
			if (!am_server) {
				usage(FERROR);
				exit_cleanup(RERR_SYNTAX);
			}
			am_sender = 1;
			break;

		case 'P':
			do_progress = 1;
			keep_partial = 1;
			break;

		case OPT_WRITE_BATCH:
			/* popt stores the filename in batch_prefix for us */
			write_batch = 1;
			break;

		case OPT_READ_BATCH:
			/* popt stores the filename in batch_prefix for us */
			read_batch = 1;
			break;

		default:
                        /* FIXME: If --daemon is specified, then errors for later
                         * parameters seem to disappear. */
                        snprintf(err_buf, sizeof(err_buf),
                                 "%s%s: %s\n",
                                 am_server ? "on remote machine: " : "",
                                 poptBadOption(pc, POPT_BADOPTION_NOALIAS),
                                 poptStrerror(opt));
                        return 0;
		}
	}

	if (write_batch && read_batch) {
	    snprintf(err_buf,sizeof(err_buf),
		"write-batch and read-batch can not be used together\n");
	    rprintf(FERROR,"ERROR: write-batch and read-batch"
		" can not be used together\n");
	    return 0;
	}

	if (do_compression && (write_batch || read_batch)) {
	    snprintf(err_buf,sizeof(err_buf),
		"compress can not be used with write-batch or read-batch\n");
	    rprintf(FERROR,"ERROR: compress can not be used with"
		"  write-batch or read-batch\n");
	    return 0;
	}

        *argv = poptGetArgs(pc);
        if (*argv)
                *argc = count_args(*argv);
        else
                *argc = 0;

	return 1;
}