	/* Redirect the worktree of the submodule in the superproject's config */
	p = git_pathdup_submodule(path, "config");
	if (!p)
		die(_("could not get submodule directory for '%s'"), path);
	git_config_set_in_file(p, "core.worktree",
			       relative_path(path, sm_gitdir, &rel_path));

	/* setup alternateLocation and alternateErrorStrategy in the cloned submodule if needed */
	git_config_get_string("submodule.alternateLocation", &sm_alternate);
	if (sm_alternate)
		git_config_set_in_file(p, "submodule.alternateLocation",
					   sm_alternate);
	git_config_get_string("submodule.alternateErrorStrategy", &error_strategy);
	if (error_strategy)
		git_config_set_in_file(p, "submodule.alternateErrorStrategy",
					   error_strategy);

	free(sm_alternate);
	free(error_strategy);

	strbuf_release(&sb);
	strbuf_release(&rel_path);
	free(sm_gitdir);
	free(path);
	free(p);
	return 0;
