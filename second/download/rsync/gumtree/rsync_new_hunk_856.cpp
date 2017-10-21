	 * that we change to some uid other than the current one, then
	 * log a warning. */

	/* TODO: Perhaps take a list of gids, and make them into the
	 * supplementary groups. */

	module_dir = lp_path(i);
	if (use_chroot) {
		if ((p = strstr(module_dir, "/./")) != NULL) {
			*p = '\0';
			p += 2;
		} else if ((p = strdup("/")) == NULL)
			out_of_memory("rsync_module");
	}

	/* We do a push_dir() that doesn't actually call chdir()
	 * just to make a relative path absolute. */
	strlcpy(line, curr_dir, sizeof line);
	if (!push_dir(module_dir, 1))
		goto chdir_failed;
	if (strcmp(curr_dir, module_dir) != 0
	 && (module_dir = strdup(curr_dir)) == NULL)
		out_of_memory("rsync_module");
	push_dir(line, 1); /* Restore curr_dir. */

	if (use_chroot) {
		chroot_path = module_dir;
		module_dir = p; /* p is "/" or our inside-chroot path */
	}
	module_dirlen = clean_fname(module_dir, CFN_COLLAPSE_DOT_DOT_DIRS | CFN_DROP_TRAILING_DOT_DIR);

	if (module_dirlen == 1) {
		module_dirlen = 0;
		set_filter_dir("/", 1);
	} else
		set_filter_dir(module_dir, module_dirlen);

	p = lp_filter(i);
	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
		   XFLG_ABS_IF_SLASH);

	p = lp_include_from(i);
