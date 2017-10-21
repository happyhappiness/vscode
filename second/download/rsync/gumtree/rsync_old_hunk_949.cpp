	 * log a warning. */

	/* TODO: Perhaps take a list of gids, and make them into the
	 * supplementary groups. */

	module_dir = lp_path(i);
	if (use_chroot) {
		if ((p = strstr(module_dir, "/./")) != NULL) {
			*p = '\0'; /* Temporary... */
			if (!(module_chdir = normalize_path(module_dir, True, NULL)))
				return path_failure(f_out, module_dir, False);
			*p = '/';
