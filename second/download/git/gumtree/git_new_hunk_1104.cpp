		* superproject did not rewrite the git file links yet,
		* fix it now.
		*/
		sub = submodule_from_path(null_sha1, path);
		if (!sub)
			die(_("could not lookup name for submodule '%s'"), path);
		connect_work_tree_and_git_dir(path,
			git_path("modules/%s", sub->name));
	} else {
		/* Is it already absorbed into the superprojects git dir? */
		char *real_sub_git_dir = real_pathdup(sub_git_dir, 1);
		char *real_common_git_dir = real_pathdup(get_git_common_dir(), 1);

		if (!starts_with(real_sub_git_dir, real_common_git_dir))
