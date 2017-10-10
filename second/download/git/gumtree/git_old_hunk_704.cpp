	/* Redirect the worktree of the submodule in the superproject's config */
	p = git_pathdup_submodule(path, "config");
	if (!p)
		die(_("could not get submodule directory for '%s'"), path);
	git_config_set_in_file(p, "core.worktree",
			       relative_path(path, sm_gitdir, &rel_path));
	strbuf_release(&sb);
	strbuf_release(&rel_path);
	free(sm_gitdir);
	free(path);
	free(p);
	return 0;
