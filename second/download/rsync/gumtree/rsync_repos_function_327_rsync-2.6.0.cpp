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

		case OPT_DELETE_AFTER:
			delete_after = 1;
			delete_mode = 1;
			break;

		case OPT_DELETE_EXCLUDED:
			delete_excluded = 1;
			delete_mode = 1;
			break;

		case OPT_EXCLUDE:
			add_exclude(&exclude_list, poptGetOptArg(pc),
				    ADD_EXCLUDE);
			break;

		case OPT_INCLUDE:
			add_exclude(&exclude_list, poptGetOptArg(pc),
				    ADD_INCLUDE);
			break;

		case OPT_EXCLUDE_FROM:
			add_exclude_file(&exclude_list, poptGetOptArg(pc),
					 MISSING_FATAL, ADD_EXCLUDE);
			break;

		case OPT_INCLUDE_FROM:
			add_exclude_file(&exclude_list, poptGetOptArg(pc),
					 MISSING_FATAL, ADD_INCLUDE);
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
			snprintf(err_buf, sizeof err_buf,
				 "hard links are not supported on this %s\n",
				 am_server ? "server" : "client");
			rprintf(FERROR, "ERROR: %s", err_buf);
			return 0;
#endif /* SUPPORT_HARD_LINKS */
			break;

		case 'v':
			verbose++;
			break;

		case 'q':
			if (frommain) quiet++;
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

		case OPT_LINK_DEST:
#if HAVE_LINK
			compare_dest = (char *)poptGetOptArg(pc);
			link_dest = 1;
			break;
#else
			snprintf(err_buf, sizeof err_buf,
				 "hard links are not supported on this %s\n",
				 am_server ? "server" : "client");
			rprintf(FERROR, "ERROR: %s", err_buf);
			return 0;
#endif


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
		rprintf(FERROR,
			"write-batch and read-batch can not be used together\n");
		exit_cleanup(RERR_SYNTAX);
	}

	if (do_compression && (write_batch || read_batch)) {
		rprintf(FERROR,
			"compress can not be used with write-batch or read-batch\n");
		exit_cleanup(RERR_SYNTAX);
	}

	if (archive_mode) {
		if (!files_from)
			recurse = 1;
#if SUPPORT_LINKS
		preserve_links = 1;
#endif
		preserve_perms = 1;
		preserve_times = 1;
		preserve_gid = 1;
		preserve_uid = 1;
		preserve_devices = 1;
	}

	if (relative_paths < 0)
		relative_paths = files_from? 1 : 0;

	if (!backup_suffix)
		backup_suffix = backup_dir? "" : BACKUP_SUFFIX;
	backup_suffix_len = strlen(backup_suffix);
	if (strchr(backup_suffix, '/') != NULL) {
		rprintf(FERROR, "--suffix cannot contain slashes: %s\n",
			backup_suffix);
		exit_cleanup(RERR_SYNTAX);
	}
	if (backup_dir)
		backup_dir_len = strlen(backup_dir);
	else if (!backup_suffix_len) {
		rprintf(FERROR,
			"--suffix cannot be a null string without --backup-dir\n");
		exit_cleanup(RERR_SYNTAX);
	}

	if (do_progress && !verbose)
		verbose = 1;

	*argv = poptGetArgs(pc);
	if (*argv)
		*argc = count_args(*argv);
	else
		*argc = 0;

	if (files_from) {
		char *colon;
		if (*argc != 2) {
			usage(FERROR);
			exit_cleanup(RERR_SYNTAX);
		}
		if (strcmp(files_from, "-") == 0) {
			filesfrom_fd = 0;
			if (am_server)
				remote_filesfrom_file = "-";
		}
		else if ((colon = find_colon(files_from)) != 0) {
			if (am_server) {
				usage(FERROR);
				exit_cleanup(RERR_SYNTAX);
			}
			remote_filesfrom_file = colon+1 + (colon[1] == ':');
			if (strcmp(remote_filesfrom_file, "-") == 0) {
				rprintf(FERROR, "Invalid --files-from remote filename\n");
				exit_cleanup(RERR_SYNTAX);
			}
		} else {
			extern int sanitize_paths;
			if (sanitize_paths)
				sanitize_path(strdup(files_from), NULL);
			filesfrom_fd = open(files_from, O_RDONLY|O_BINARY);
			if (filesfrom_fd < 0) {
				rsyserr(FERROR, errno,
					"failed to open files-from file %s",
					files_from);
				exit_cleanup(RERR_FILEIO);
			}
		}
	}

	return 1;
}