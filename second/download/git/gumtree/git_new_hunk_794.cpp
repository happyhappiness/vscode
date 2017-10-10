		sub = submodule_from_path(null_sha1, path);
		if (!sub)
			die(_("could not lookup name for submodule '%s'"), path);
		new_git_dir = git_path("modules/%s", sub->name);
		if (safe_create_leading_directories_const(new_git_dir) < 0)
			die(_("could not create directory '%s'"), new_git_dir);
		real_new_git_dir = real_pathdup(new_git_dir, 1);
		connect_work_tree_and_git_dir(path, real_new_git_dir);

		free(real_new_git_dir);
	} else {
		/* Is it already absorbed into the superprojects git dir? */
		char *real_sub_git_dir = real_pathdup(sub_git_dir, 1);
		char *real_common_git_dir = real_pathdup(get_git_common_dir(), 1);

		if (!starts_with(real_sub_git_dir, real_common_git_dir))
			relocate_single_git_dir_into_superproject(prefix, path);

		free(real_sub_git_dir);
		free(real_common_git_dir);
