int parse_arguments(int *argc_p, const char ***argv_p)
{
	static poptContext pc;
	char *ref = lp_refuse_options(module_id);
	const char *arg, **argv = *argv_p;
	int argc = *argc_p;
	int opt;

	if (ref && *ref)
		set_refuse_options(ref);
	if (am_daemon) {
		set_refuse_options("log-file*");
#ifdef ICONV_OPTION
		if (!*lp_charset(module_id))
			set_refuse_options("iconv");
#endif
	}

#ifdef ICONV_OPTION
	if (!am_daemon && !protect_args && (arg = getenv("RSYNC_ICONV")) != NULL && *arg)
		iconv_opt = strdup(arg);
#endif

	/* TODO: Call poptReadDefaultConfig; handle errors. */

	/* The context leaks in case of an error, but if there's a
	 * problem we always exit anyhow. */
	if (pc)
		poptFreeContext(pc);
	pc = poptGetContext(RSYNC_NAME, argc, argv, long_options, 0);
	if (!am_server)
		poptReadDefaultConfig(pc, 0);

	while ((opt = poptGetNextOpt(pc)) != -1) {
		/* most options are handled automatically by popt;
		 * only special cases are returned and listed here. */

		switch (opt) {
		case OPT_VERSION:
			print_rsync_version(FINFO);
			exit_cleanup(0);

		case OPT_SERVER:
			if (!am_server) {
				/* Disable popt aliases on the server side and
				 * then start parsing the options again. */
				poptFreeContext(pc);
				pc = poptGetContext(RSYNC_NAME, argc, argv,
						    long_options, 0);
				am_server = 1;
			}
#ifdef ICONV_OPTION
			iconv_opt = NULL;
#endif
			break;

		case OPT_SENDER:
			if (!am_server) {
				usage(FERROR);
				exit_cleanup(RERR_SYNTAX);
			}
			am_sender = 1;
			break;

		case OPT_DAEMON:
			if (am_daemon) {
				strlcpy(err_buf,
					"Attempt to hack rsync thwarted!\n",
					sizeof err_buf);
				return 0;
			}
#ifdef ICONV_OPTION
			iconv_opt = NULL;
#endif
			poptFreeContext(pc);
			pc = poptGetContext(RSYNC_NAME, argc, argv,
					    long_daemon_options, 0);
			while ((opt = poptGetNextOpt(pc)) != -1) {
				switch (opt) {
				case 'h':
					daemon_usage(FINFO);
					exit_cleanup(0);

				case 'v':
					verbose++;
					break;

				default:
					rprintf(FERROR,
					    "rsync: %s: %s (in daemon mode)\n",
					    poptBadOption(pc, POPT_BADOPTION_NOALIAS),
					    poptStrerror(opt));
					goto daemon_error;
				}
			}

			if (tmpdir && strlen(tmpdir) >= MAXPATHLEN - 10) {
				snprintf(err_buf, sizeof err_buf,
					 "the --temp-dir path is WAY too long.\n");
				return 0;
			}

			if (!daemon_opt) {
				rprintf(FERROR, "Daemon option(s) used without --daemon.\n");
			    daemon_error:
				rprintf(FERROR,
				    "(Type \"rsync --daemon --help\" for assistance with daemon mode.)\n");
				exit_cleanup(RERR_SYNTAX);
			}

			*argv_p = argv = poptGetArgs(pc);
			*argc_p = argc = count_args(argv);
			am_starting_up = 0;
			daemon_opt = 0;
			am_daemon = 1;
			return 1;

		case OPT_MODIFY_WINDOW:
			/* The value has already been set by popt, but
			 * we need to remember that we're using a
			 * non-default setting. */
			modify_window_set = 1;
			break;

		case OPT_FILTER:
			parse_rule(&filter_list, poptGetOptArg(pc), 0, 0);
			break;

		case OPT_EXCLUDE:
			parse_rule(&filter_list, poptGetOptArg(pc),
				   0, XFLG_OLD_PREFIXES);
			break;

		case OPT_INCLUDE:
			parse_rule(&filter_list, poptGetOptArg(pc),
				   MATCHFLG_INCLUDE, XFLG_OLD_PREFIXES);
			break;

		case OPT_EXCLUDE_FROM:
		case OPT_INCLUDE_FROM:
			arg = poptGetOptArg(pc);
			if (sanitize_paths)
				arg = sanitize_path(NULL, arg, NULL, 0, SP_DEFAULT);
			if (daemon_filter_list.head) {
				int rej;
				char *dir, *cp = strdup(arg);
				if (!cp)
					out_of_memory("parse_arguments");
				if (!*cp)
					goto options_rejected;
				dir = cp + (*cp == '/' ? module_dirlen : 0);
				clean_fname(dir, CFN_COLLAPSE_DOT_DOT_DIRS);
				rej = check_filter(&daemon_filter_list, FLOG, dir, 0) < 0;
				free(cp);
				if (rej)
					goto options_rejected;
			}
			parse_filter_file(&filter_list, arg,
				opt == OPT_INCLUDE_FROM ? MATCHFLG_INCLUDE : 0,
				XFLG_FATAL_ERRORS | XFLG_OLD_PREFIXES);
			break;

		case 'a':
			if (refused_archive_part) {
				create_refuse_error(refused_archive_part);
				return 0;
			}
			if (!recurse) /* preserve recurse == 2 */
				recurse = 1;
#ifdef SUPPORT_LINKS
			preserve_links = 1;
#endif
			preserve_perms = 1;
			preserve_times = 1;
			preserve_gid = 1;
			preserve_uid = 1;
			preserve_devices = 1;
			preserve_specials = 1;
			break;

		case 'D':
			preserve_devices = preserve_specials = 1;
			break;

		case OPT_NO_D:
			preserve_devices = preserve_specials = 0;
			break;

		case 'h':
			human_readable++;
			break;

		case 'H':
			preserve_hard_links++;
			break;

		case 'i':
			itemize_changes++;
			break;

		case 'v':
			verbose++;
			break;

		case 'q':
			quiet++;
			break;

		case 'x':
			one_file_system++;
			break;

		case 'F':
			switch (++F_option_cnt) {
			case 1:
				parse_rule(&filter_list,": /.rsync-filter",0,0);
				break;
			case 2:
				parse_rule(&filter_list,"- .rsync-filter",0,0);
				break;
			}
			break;

		case 'P':
			if (refused_partial || refused_progress) {
				create_refuse_error(refused_partial
				    ? refused_partial : refused_progress);
				return 0;
			}
			do_progress = 1;
			keep_partial = 1;
			break;

		case 'z':
			if (def_compress_level < Z_DEFAULT_COMPRESSION
			 || def_compress_level > Z_BEST_COMPRESSION) {
				snprintf(err_buf, sizeof err_buf,
					"--compress-level value is invalid: %d\n",
					def_compress_level);
				return 0;
			}
			do_compression = def_compress_level != Z_NO_COMPRESSION;
			if (do_compression && refused_compress) {
				create_refuse_error(refused_compress);
				return 0;
			}
			break;

		case OPT_WRITE_BATCH:
			/* batch_name is already set */
			write_batch = 1;
			break;

		case OPT_ONLY_WRITE_BATCH:
			/* batch_name is already set */
			write_batch = -1;
			break;

		case OPT_READ_BATCH:
			/* batch_name is already set */
			read_batch = 1;
			break;

		case OPT_NO_ICONV:
#ifdef ICONV_OPTION
			iconv_opt = NULL;
#endif
			break;

		case OPT_MAX_SIZE:
			if ((max_size = parse_size_arg(&max_size_arg, 'b')) <= 0) {
				snprintf(err_buf, sizeof err_buf,
					"--max-size value is invalid: %s\n",
					max_size_arg);
				return 0;
			}
			break;

		case OPT_MIN_SIZE:
			if ((min_size = parse_size_arg(&min_size_arg, 'b')) <= 0) {
				snprintf(err_buf, sizeof err_buf,
					"--min-size value is invalid: %s\n",
					min_size_arg);
				return 0;
			}
			break;

		case OPT_APPEND:
			if (am_server)
				append_mode++;
			else
				append_mode = 1;
			break;

		case OPT_LINK_DEST:
#ifdef SUPPORT_HARD_LINKS
			link_dest = 1;
			dest_option = "--link-dest";
			goto set_dest_dir;
#else
			snprintf(err_buf, sizeof err_buf,
				 "hard links are not supported on this %s\n",
				 am_server ? "server" : "client");
			return 0;
#endif

		case OPT_COPY_DEST:
			copy_dest = 1;
			dest_option = "--copy-dest";
			goto set_dest_dir;

		case OPT_COMPARE_DEST:
			compare_dest = 1;
			dest_option = "--compare-dest";
		set_dest_dir:
			if (basis_dir_cnt >= MAX_BASIS_DIRS) {
				snprintf(err_buf, sizeof err_buf,
					"ERROR: at most %d %s args may be specified\n",
					MAX_BASIS_DIRS, dest_option);
				return 0;
			}
			/* We defer sanitizing this arg until we know what
			 * our destination directory is going to be. */
			basis_dir[basis_dir_cnt++] = (char *)poptGetOptArg(pc);
			break;

		case OPT_CHMOD:
			arg = poptGetOptArg(pc);
			if (!parse_chmod(arg, &chmod_modes)) {
				snprintf(err_buf, sizeof err_buf,
				    "Invalid argument passed to --chmod (%s)\n",
				    arg);
				return 0;
			}
			break;

		case OPT_HELP:
			usage(FINFO);
			exit_cleanup(0);

		case 'A':
#ifdef SUPPORT_ACLS
			preserve_acls = 1;
			preserve_perms = 1;
			break;
#else
			/* FIXME: this should probably be ignored with a
			 * warning and then countermeasures taken to
			 * restrict group and other access in the presence
			 * of any more restrictive ACLs, but this is safe
			 * for now */
			snprintf(err_buf,sizeof(err_buf),
                                 "ACLs are not supported on this %s\n",
				 am_server ? "server" : "client");
			return 0;
#endif

		case 'X':
#ifdef SUPPORT_XATTRS
			preserve_xattrs++;
			break;
#else
			snprintf(err_buf,sizeof(err_buf),
				 "extended attributes are not supported on this %s\n",
				 am_server ? "server" : "client");
			return 0;
#endif

		default:
			/* A large opt value means that set_refuse_options()
			 * turned this option off. */
			if (opt >= OPT_REFUSED_BASE) {
				create_refuse_error(opt);
				return 0;
			}
			snprintf(err_buf, sizeof err_buf, "%s%s: %s\n",
				 am_server ? "on remote machine: " : "",
				 poptBadOption(pc, POPT_BADOPTION_NOALIAS),
				 poptStrerror(opt));
			return 0;
		}
	}

	if (human_readable && argc == 2 && !am_server) {
		/* Allow the old meaning of 'h' (--help) on its own. */
		usage(FINFO);
		exit_cleanup(0);
	}

#ifdef ICONV_OPTION
	if (iconv_opt && protect_args != 2) {
		if (!am_server && strcmp(iconv_opt, "-") == 0)
			iconv_opt = NULL;
		else
			need_unsorted_flist = 1;
	}
	if (refused_no_iconv && !iconv_opt) {
		create_refuse_error(refused_no_iconv);
		return 0;
	}
#endif

	if (protect_args == 1 && am_server)
		return 1;

	*argv_p = argv = poptGetArgs(pc);
	*argc_p = argc = count_args(argv);

#ifndef SUPPORT_LINKS
	if (preserve_links && !am_sender) {
		snprintf(err_buf, sizeof err_buf,
			 "symlinks are not supported on this %s\n",
			 am_server ? "server" : "client");
		return 0;
	}
#endif

#ifndef SUPPORT_HARD_LINKS
	if (preserve_hard_links) {
		snprintf(err_buf, sizeof err_buf,
			 "hard links are not supported on this %s\n",
			 am_server ? "server" : "client");
		return 0;
	}
#endif

#ifdef SUPPORT_XATTRS
	if (am_root < 0 && preserve_xattrs > 1) {
		snprintf(err_buf, sizeof err_buf,
			 "--fake-super conflicts with -XX\n");
		return 0;
	}
#else
	if (am_root < 0) {
		snprintf(err_buf, sizeof err_buf,
			 "--fake-super requires an rsync with extended attributes enabled\n");
		return 0;
	}
#endif

	if (write_batch && read_batch) {
		snprintf(err_buf, sizeof err_buf,
			"--write-batch and --read-batch can not be used together\n");
		return 0;
	}
	if (write_batch > 0 || read_batch) {
		if (am_server) {
			rprintf(FINFO,
				"ignoring --%s-batch option sent to server\n",
				write_batch ? "write" : "read");
			/* We don't actually exit_cleanup(), so that we can
			 * still service older version clients that still send
			 * batch args to server. */
			read_batch = write_batch = 0;
			batch_name = NULL;
		} else if (dry_run)
			write_batch = 0;
	} else if (write_batch < 0 && dry_run)
		write_batch = 0;
	if (read_batch && files_from) {
		snprintf(err_buf, sizeof err_buf,
			"--read-batch cannot be used with --files-from\n");
		return 0;
	}
	if (read_batch && remove_source_files) {
		snprintf(err_buf, sizeof err_buf,
			"--read-batch cannot be used with --remove-%s-files\n",
			remove_source_files == 1 ? "source" : "sent");
		return 0;
	}
	if (batch_name && strlen(batch_name) > MAX_BATCH_NAME_LEN) {
		snprintf(err_buf, sizeof err_buf,
			"the batch-file name must be %d characters or less.\n",
			MAX_BATCH_NAME_LEN);
		return 0;
	}

	if (tmpdir && strlen(tmpdir) >= MAXPATHLEN - 10) {
		snprintf(err_buf, sizeof err_buf,
			 "the --temp-dir path is WAY too long.\n");
		return 0;
	}

	if (max_delete < 0 && max_delete != INT_MIN) {
		/* Negative numbers are treated as "no deletions". */
		max_delete = 0;
	}

	if (compare_dest + copy_dest + link_dest > 1) {
		snprintf(err_buf, sizeof err_buf,
			"You may not mix --compare-dest, --copy-dest, and --link-dest.\n");
		return 0;
	}

	if (files_from) {
		if (recurse == 1) /* preserve recurse == 2 */
			recurse = 0;
		if (xfer_dirs < 0)
			xfer_dirs = 1;
	}

	if (argc < 2 && !read_batch && !am_server)
		list_only |= 1;

	if (xfer_dirs >= 4) {
		parse_rule(&filter_list, "- /*/*", 0, 0);
		recurse = xfer_dirs = 1;
	} else if (recurse)
		xfer_dirs = 1;
	else if (xfer_dirs < 0)
		xfer_dirs = list_only ? 1 : 0;

	if (relative_paths < 0)
		relative_paths = files_from? 1 : 0;
	if (!relative_paths)
		implied_dirs = 0;

	if (delete_before + !!delete_during + delete_after > 1) {
		snprintf(err_buf, sizeof err_buf,
			"You may not combine multiple --delete-WHEN options.\n");
		return 0;
	}
	if (delete_before || delete_during || delete_after)
		delete_mode = 1;
	else if (delete_mode || delete_excluded) {
		/* Only choose now between before & during if one is refused. */
		if (refused_delete_before) {
			if (!refused_delete_during)
				delete_during = 1;
			else {
				create_refuse_error(refused_delete_before);
				return 0;
			}
		} else if (refused_delete_during)
			delete_before = 1;
		delete_mode = 1;
	}
	if (!xfer_dirs && delete_mode) {
		snprintf(err_buf, sizeof err_buf,
			"--delete does not work without --recursive (-r) or --dirs (-d).\n");
		return 0;
	}

	if (delete_mode && refused_delete) {
		create_refuse_error(refused_delete);
		return 0;
	}

	if (remove_source_files) {
		/* We only want to infer this refusal of --remove-source-files
		 * via the refusal of "delete", not any of the "delete-FOO"
		 * options. */
		if (refused_delete && am_sender) {
			create_refuse_error(refused_delete);
			return 0;
		}
		need_messages_from_generator = 1;
	}

	if (sanitize_paths) {
		int i;
		for (i = argc; i-- > 0; )
			argv[i] = sanitize_path(NULL, argv[i], "", 0, SP_KEEP_DOT_DIRS);
		if (tmpdir)
			tmpdir = sanitize_path(NULL, tmpdir, NULL, 0, SP_DEFAULT);
		if (backup_dir)
			backup_dir = sanitize_path(NULL, backup_dir, NULL, 0, SP_DEFAULT);
	}
	if (daemon_filter_list.head && !am_sender) {
		struct filter_list_struct *elp = &daemon_filter_list;
		if (tmpdir) {
			char *dir;
			if (!*tmpdir)
				goto options_rejected;
			dir = tmpdir + (*tmpdir == '/' ? module_dirlen : 0);
			clean_fname(dir, CFN_COLLAPSE_DOT_DOT_DIRS);
			if (check_filter(elp, FLOG, dir, 1) < 0)
				goto options_rejected;
		}
		if (backup_dir) {
			char *dir;
			if (!*backup_dir)
				goto options_rejected;
			dir = backup_dir + (*backup_dir == '/' ? module_dirlen : 0);
			clean_fname(dir, CFN_COLLAPSE_DOT_DOT_DIRS);
			if (check_filter(elp, FLOG, dir, 1) < 0)
				goto options_rejected;
		}
	}

	if (!backup_suffix)
		backup_suffix = backup_dir ? "" : BACKUP_SUFFIX;
	backup_suffix_len = strlen(backup_suffix);
	if (strchr(backup_suffix, '/') != NULL) {
		snprintf(err_buf, sizeof err_buf,
			"--suffix cannot contain slashes: %s\n",
			backup_suffix);
		return 0;
	}
	if (backup_dir) {
		size_t len = strlcpy(backup_dir_buf, backup_dir, sizeof backup_dir_buf);
		if (len > sizeof backup_dir_buf - 128) {
			snprintf(err_buf, sizeof err_buf,
				"the --backup-dir path is WAY too long.\n");
			return 0;
		}
		backup_dir_len = (int)len;
		if (backup_dir_buf[backup_dir_len - 1] != '/') {
			backup_dir_buf[backup_dir_len++] = '/';
			backup_dir_buf[backup_dir_len] = '\0';
		}
		backup_dir_remainder = sizeof backup_dir_buf - backup_dir_len;
		if (verbose > 1 && !am_sender)
			rprintf(FINFO, "backup_dir is %s\n", backup_dir_buf);
	} else if (!backup_suffix_len && (!am_server || !am_sender)) {
		snprintf(err_buf, sizeof err_buf,
			"--suffix cannot be a null string without --backup-dir\n");
		return 0;
	} else if (make_backups && delete_mode && !delete_excluded && !am_server) {
		snprintf(backup_dir_buf, sizeof backup_dir_buf,
			"P *%s", backup_suffix);
		parse_rule(&filter_list, backup_dir_buf, 0, 0);
	}

	if (preserve_times) {
		preserve_times = PRESERVE_FILE_TIMES;
		if (!omit_dir_times)
			preserve_times |= PRESERVE_DIR_TIMES;
#ifdef CAN_SET_SYMLINK_TIMES
		preserve_times |= PRESERVE_LINK_TIMES;
#endif
	}

	if (make_backups && !backup_dir) {
		omit_dir_times = 0; /* Implied, so avoid -O to sender. */
		preserve_times &= ~PRESERVE_DIR_TIMES;
	}

	if (stdout_format) {
		if (am_server && log_format_has(stdout_format, 'I'))
			stdout_format_has_i = 2;
		else if (log_format_has(stdout_format, 'i'))
			stdout_format_has_i = itemize_changes | 1;
		if (!log_format_has(stdout_format, 'b')
		 && !log_format_has(stdout_format, 'c'))
			log_before_transfer = !am_server;
	} else if (itemize_changes) {
		stdout_format = "%i %n%L";
		stdout_format_has_i = itemize_changes;
		log_before_transfer = !am_server;
	}

	if (do_progress && !verbose && !log_before_transfer && !am_server)
		verbose = 1;

	if (dry_run)
		do_xfers = 0;

	set_io_timeout(io_timeout);

	if (verbose && !stdout_format) {
		stdout_format = "%n%L";
		log_before_transfer = !am_server;
	}
	if (stdout_format_has_i || log_format_has(stdout_format, 'o'))
		stdout_format_has_o_or_i = 1;

	if (logfile_name && !am_daemon) {
		if (!logfile_format) {
			logfile_format = "%i %n%L";
			logfile_format_has_i = logfile_format_has_o_or_i = 1;
		} else {
			if (log_format_has(logfile_format, 'i'))
				logfile_format_has_i = 1;
			if (logfile_format_has_i || log_format_has(logfile_format, 'o'))
				logfile_format_has_o_or_i = 1;
		}
		log_init(0);
	} else if (!am_daemon)
		logfile_format = NULL;

	if (daemon_bwlimit && (!bwlimit || bwlimit > daemon_bwlimit))
		bwlimit = daemon_bwlimit;
	if (bwlimit) {
		bwlimit_writemax = (size_t)bwlimit * 128;
		if (bwlimit_writemax < 512)
			bwlimit_writemax = 512;
	}

	if (sparse_files && inplace) {
		/* Note: we don't check for this below, because --append is
		 * OK with --sparse (as long as redos are handled right). */
		snprintf(err_buf, sizeof err_buf,
			 "--sparse cannot be used with --inplace\n");
		return 0;
	}

	if (append_mode) {
		if (whole_file > 0) {
			snprintf(err_buf, sizeof err_buf,
				 "--append cannot be used with --whole-file\n");
			return 0;
		}
		if (refused_inplace) {
			create_refuse_error(refused_inplace);
			return 0;
		}
		inplace = 1;
	}

	if (delay_updates && !partial_dir)
		partial_dir = tmp_partialdir;

	if (inplace) {
#ifdef HAVE_FTRUNCATE
		if (partial_dir) {
			snprintf(err_buf, sizeof err_buf,
				 "--%s cannot be used with --%s\n",
				 append_mode ? "append" : "inplace",
				 delay_updates ? "delay-updates" : "partial-dir");
			return 0;
		}
		/* --inplace implies --partial for refusal purposes, but we
		 * clear the keep_partial flag for internal logic purposes. */
		if (refused_partial) {
			create_refuse_error(refused_partial);
			return 0;
		}
		keep_partial = 0;
#else
		snprintf(err_buf, sizeof err_buf,
			 "--%s is not supported on this %s\n",
			 append_mode ? "append" : "inplace",
			 am_server ? "server" : "client");
		return 0;
#endif
	} else {
		if (keep_partial && !partial_dir && !am_server) {
			if ((arg = getenv("RSYNC_PARTIAL_DIR")) != NULL && *arg)
				partial_dir = strdup(arg);
		}
		if (partial_dir) {
			if (*partial_dir)
				clean_fname(partial_dir, CFN_COLLAPSE_DOT_DOT_DIRS);
			if (!*partial_dir || strcmp(partial_dir, ".") == 0)
				partial_dir = NULL;
			if (!partial_dir && refused_partial) {
				create_refuse_error(refused_partial);
				return 0;
			}
			keep_partial = 1;
		}
	}

	if (files_from) {
		char *h, *p;
		int q;
		if (argc > 2 || (!am_daemon && argc == 1)) {
			usage(FERROR);
			exit_cleanup(RERR_SYNTAX);
		}
		if (strcmp(files_from, "-") == 0) {
			filesfrom_fd = 0;
			if (am_server)
				filesfrom_host = ""; /* reading from socket */
		} else if ((p = check_for_hostspec(files_from, &h, &q)) != 0) {
			if (am_server) {
				snprintf(err_buf, sizeof err_buf,
					"The --files-from sent to the server cannot specify a host.\n");
				return 0;
			}
			files_from = p;
			filesfrom_host = h;
			if (strcmp(files_from, "-") == 0) {
				snprintf(err_buf, sizeof err_buf,
					"Invalid --files-from remote filename\n");
				return 0;
			}
		} else {
			if (sanitize_paths)
				files_from = sanitize_path(NULL, files_from, NULL, 0, SP_DEFAULT);
			if (daemon_filter_list.head) {
				char *dir;
				if (!*files_from)
					goto options_rejected;
				dir = files_from + (*files_from == '/' ? module_dirlen : 0);
				clean_fname(dir, CFN_COLLAPSE_DOT_DOT_DIRS);
				if (check_filter(&daemon_filter_list, FLOG, dir, 0) < 0)
					goto options_rejected;
			}
			filesfrom_fd = open(files_from, O_RDONLY|O_BINARY);
			if (filesfrom_fd < 0) {
				snprintf(err_buf, sizeof err_buf,
					"failed to open files-from file %s: %s\n",
					files_from, strerror(errno));
				return 0;
			}
		}
	}

	am_starting_up = 0;

	return 1;

  options_rejected:
	snprintf(err_buf, sizeof err_buf,
		"Your options have been rejected by the server.\n");
	return 0;
}