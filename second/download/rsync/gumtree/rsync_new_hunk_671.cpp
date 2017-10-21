		p = lp_uid(i);
		if (!name_to_uid(p, &uid)) {
			if (!isdigit(* (unsigned char *) p)) {
				rprintf(FERROR,"Invalid uid %s\n", p);
				io_printf(f_out, "@ERROR: invalid uid %s\n", p);
				return -1;
			}
			uid = atoi(p);
		}

		p = lp_gid(i);
		if (!name_to_gid(p, &gid)) {
			if (!isdigit(* (unsigned char *) p)) {
				rprintf(FERROR,"Invalid gid %s\n", p);
				io_printf(f_out, "@ERROR: invalid gid %s\n", p);
				return -1;
			}
			gid = atoi(p);
		}
	}

        /* TODO: If we're not root, but the configuration requests
         * that we change to some uid other than the current one, then
         * log a warning. */

        /* TODO: Perhaps take a list of gids, and make them into the
         * supplementary groups. */

	exclude_path_prefix = use_chroot? "" : lp_path(i);
	if (*exclude_path_prefix == '/' && !exclude_path_prefix[1])
		exclude_path_prefix = "";

	p = lp_include_from(i);
	add_exclude_file(&server_exclude_list, p, MISSING_FATAL, ADD_INCLUDE);

	p = lp_include(i);
	add_exclude_line(&server_exclude_list, p, ADD_INCLUDE);

	p = lp_exclude_from(i);
	add_exclude_file(&server_exclude_list, p, MISSING_FATAL, ADD_EXCLUDE);

	p = lp_exclude(i);
	add_exclude_line(&server_exclude_list, p, ADD_EXCLUDE);

	exclude_path_prefix = NULL;

	log_init();

	if (use_chroot) {
		/*
		 * XXX: The 'use chroot' flag is a fairly reliable
