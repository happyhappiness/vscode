int parse_arguments(int *argc, const char ***argv, int frommain)
{
	int opt;
	char *ref = lp_refuse_options(module_id);
	const char *arg;
	poptContext pc;

	if (ref && *ref)
		set_refuse_options(ref);

	/* TODO: Call poptReadDefaultConfig; handle errors. */

	/* The context leaks in case of an error, but if there's a
	 * problem we always exit anyhow. */
	pc = poptGetContext(RSYNC_NAME, *argc, *argv, long_options, 0);

	while ((opt = poptGetNextOpt(pc)) != -1) {
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
			add_exclude(&exclude_list, poptGetOptArg(pc), 0);
			break;

		case OPT_INCLUDE:
			add_exclude(&exclude_list, poptGetOptArg(pc),
				    XFLG_DEF_INCLUDE);
			break;

		case OPT_EXCLUDE_FROM:
			arg = poptGetOptArg(pc);
			if (sanitize_paths)
				arg = alloc_sanitize_path(arg, curr_dir);
			add_exclude_file(&exclude_list, arg,
					 XFLG_FATAL_ERRORS);
			break;

		case OPT_INCLUDE_FROM:
			arg = poptGetOptArg(pc);
			if (sanitize_paths)
				arg = alloc_sanitize_path(arg, curr_dir);
			add_exclude_file(&exclude_list, arg,
					 XFLG_FATAL_ERRORS | XFLG_DEF_INCLUDE);
			break;

		case 'h':
			usage(FINFO);
			exit_cleanup(0);

		case 'v':
			verbose++;
			break;

		case 'q':
			if (frommain)
				quiet++;
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
			checksum_seed = FIXED_CHECKSUM_SEED;
			break;

		case OPT_READ_BATCH:
			/* popt stores the filename in batch_prefix for us */
			read_batch = 1;
			checksum_seed = FIXED_CHECKSUM_SEED;
			break;

		case OPT_LINK_DEST:
#if HAVE_LINK
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
			/* A large opt value means that set_refuse_options()
			 * turned this option off (opt-BASE is its index). */
			if (opt >= OPT_REFUSED_BASE) {
				struct poptOption *op =
				    &long_options[opt-OPT_REFUSED_BASE];
				int n = snprintf(err_buf, sizeof err_buf,
				    "This server does not support --%s\n",
				    op->longName) - 1;
				if (op->shortName) {
					snprintf(err_buf+n, sizeof err_buf-n,
					    " (-%c)\n", op->shortName);
				}
			} else {
				snprintf(err_buf, sizeof err_buf,
				    "%s%s: %s\n",
				    am_server ? "on remote machine: " : "",
				    poptBadOption(pc, POPT_BADOPTION_NOALIAS),
				    poptStrerror(opt));
			}
			return 0;
		}
	}

#if !SUPPORT_LINKS
	if (preserve_links && !am_sender) {
		snprintf(err_buf, sizeof err_buf,
			 "symlinks are not supported on this %s\n",
			 am_server ? "server" : "client");
		rprintf(FERROR, "ERROR: %s", err_buf);
		return 0;
	}
#endif

#if !SUPPORT_HARD_LINKS
	if (preserve_hard_links) {
		snprintf(err_buf, sizeof err_buf,
			 "hard links are not supported on this %s\n",
			 am_server ? "server" : "client");
		rprintf(FERROR, "ERROR: %s", err_buf);
		return 0;
	}
#endif

	if (write_batch && read_batch) {
		rprintf(FERROR,
			"write-batch and read-batch can not be used together\n");
		exit_cleanup(RERR_SYNTAX);
	}
	if (batch_prefix && strlen(batch_prefix) > MAX_BATCH_PREFIX_LEN) {
		rprintf(FERROR,
			"the batch-file prefix must be %d characters or less.\n",
			MAX_BATCH_PREFIX_LEN);
		exit_cleanup(RERR_SYNTAX);
	}

	if (tmpdir && strlen(tmpdir) >= MAXPATHLEN - 10) {
		rprintf(FERROR, "the --temp-dir path is WAY too long.\n");
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

	*argv = poptGetArgs(pc);
	if (*argv)
		*argc = count_args(*argv);
	else
		*argc = 0;

	if (sanitize_paths) {
		int i;
		for (i = *argc; i-- > 0; )
			(*argv)[i] = alloc_sanitize_path((*argv)[i], NULL);
		if (tmpdir)
			tmpdir = alloc_sanitize_path(tmpdir, curr_dir);
		if (compare_dest)
			compare_dest = alloc_sanitize_path(compare_dest, curr_dir);
		if (backup_dir)
			backup_dir = alloc_sanitize_path(backup_dir, curr_dir);
		if (files_from)
			files_from = alloc_sanitize_path(files_from, curr_dir);
	}

	if (daemon_opt) {
		daemon_opt = 0;
		am_daemon = 1;
		return 1;
	}

	if (!backup_suffix)
		backup_suffix = backup_dir ? "" : BACKUP_SUFFIX;
	backup_suffix_len = strlen(backup_suffix);
	if (strchr(backup_suffix, '/') != NULL) {
		rprintf(FERROR, "--suffix cannot contain slashes: %s\n",
			backup_suffix);
		exit_cleanup(RERR_SYNTAX);
	}
	if (backup_dir) {
		backup_dir_len = strlcpy(backup_dir_buf, backup_dir, sizeof backup_dir_buf);
		backup_dir_remainder = sizeof backup_dir_buf - backup_dir_len;
		if (backup_dir_remainder < 32) {
			rprintf(FERROR, "the --backup-dir path is WAY too long.\n");
			exit_cleanup(RERR_SYNTAX);
		}
		if (backup_dir_buf[backup_dir_len - 1] != '/') {
			backup_dir_buf[backup_dir_len++] = '/';
			backup_dir_buf[backup_dir_len] = '\0';
		}
		if (verbose > 1 && !am_sender)
			rprintf(FINFO, "backup_dir is %s\n", backup_dir_buf);
	} else if (!backup_suffix_len && (!am_server || !am_sender)) {
		rprintf(FERROR,
			"--suffix cannot be a null string without --backup-dir\n");
		exit_cleanup(RERR_SYNTAX);
	}

	if (do_progress && !verbose)
		verbose = 1;

	if (files_from) {
		char *colon;
		if (*argc != 2 && !(am_server && am_sender && *argc == 1)) {
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