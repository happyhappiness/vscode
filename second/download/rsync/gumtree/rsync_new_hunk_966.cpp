			/* This should only be able to happen in a batch. */
			fprintf(stderr,
			    "Incompatible options specified for inc-recursive %s.\n",
			    read_batch ? "batch file" : "connection");
			exit_cleanup(RERR_SYNTAX);
		}
		use_safe_inc_flist = (compat_flags & CF_SAFE_FLIST) || protocol_version >= 31;
		need_messages_from_generator = 1;
#ifdef CAN_SET_SYMLINK_TIMES
	} else if (!am_sender) {
		receiver_symlink_times = 1;
#endif
	}

	if (need_unsorted_flist && (!am_sender || inc_recurse))
		unsort_ndx = ++file_extra_cnt;

	if (partial_dir && *partial_dir != '/' && (!am_server || local_server)) {
		int rflags = FILTRULE_NO_PREFIXES | FILTRULE_DIRECTORY;
		if (!am_sender || protocol_version >= 30)
			rflags |= FILTRULE_PERISHABLE;
		parse_filter_str(&filter_list, partial_dir, rule_template(rflags), 0);
	}


#ifdef ICONV_OPTION
	if (protect_args && files_from) {
		if (am_sender)
