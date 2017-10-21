	/* TODO: Perhaps take a list of gids, and make them into the
	 * supplementary groups. */

	module_dir = lp_path(i);
	if (use_chroot) {
		if ((p = strstr(module_dir, "/./")) != NULL) {
			*p = '\0'; /* Temporary... */
			if (!(module_chdir = normalize_path(module_dir, True, NULL)))
				return path_failure(f_out, module_dir, False);
			*p = '/';
			if (!(p = normalize_path(p + 2, True, &module_dirlen)))
				return path_failure(f_out, strstr(module_dir, "/./"), False);
			if (!(full_module_path = normalize_path(module_dir, False, NULL)))
				full_module_path = module_dir;
			module_dir = p;
		} else {
			if (!(module_chdir = normalize_path(module_dir, False, NULL)))
				return path_failure(f_out, module_dir, False);
			full_module_path = module_chdir;
			module_dir = "/";
			module_dirlen = 1;
		}
	} else {
		if (!(module_chdir = normalize_path(module_dir, False, &module_dirlen)))
			return path_failure(f_out, module_dir, False);
		full_module_path = module_dir = module_chdir;
	}

	if (module_dirlen == 1) {
		module_dirlen = 0;
		set_filter_dir("/", 1);
	} else
		set_filter_dir(module_dir, module_dirlen);
