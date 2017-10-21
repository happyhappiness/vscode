
	module_dir = lp_path(i);
	if (use_chroot) {
		if ((p = strstr(module_dir, "/./")) != NULL) {
			*p = '\0';
			p += 2;
		} else if ((p = strdup("/")) == NULL) /* MEMORY LEAK */
			out_of_memory("rsync_module");
	}

	/* We do a change_dir() that doesn't actually call chdir()
	 * just to make a relative path absolute. */
	strlcpy(line, curr_dir, sizeof line);
	if (!change_dir(module_dir, CD_SKIP_CHDIR))
		goto chdir_failed;
	if (strcmp(curr_dir, module_dir) != 0
	 && (module_dir = strdup(curr_dir)) == NULL)
		out_of_memory("rsync_module");
	change_dir(line, CD_SKIP_CHDIR); /* Restore curr_dir. */

	if (use_chroot) {
		chroot_path = module_dir;
		module_dir = p; /* p is "/" or our inside-chroot path */
	}
	module_dirlen = clean_fname(module_dir, CFN_COLLAPSE_DOT_DOT_DIRS | CFN_DROP_TRAILING_DOT_DIR);
