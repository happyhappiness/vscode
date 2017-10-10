			die(_("could not create directory '%s'"), path);
		strbuf_addf(&sb, "%s/index", sm_gitdir);
		unlink_or_warn(sb.buf);
		strbuf_reset(&sb);
	}

	/* Write a .git file in the submodule to redirect to the superproject. */
	strbuf_addf(&sb, "%s/.git", path);
	if (safe_create_leading_directories_const(sb.buf) < 0)
		die(_("could not create leading directories of '%s'"), sb.buf);
	submodule_dot_git = fopen(sb.buf, "w");
	if (!submodule_dot_git)
		die_errno(_("cannot open file '%s'"), sb.buf);

	fprintf_or_die(submodule_dot_git, "gitdir: %s\n",
		       relative_path(sm_gitdir, path, &rel_path));
	if (fclose(submodule_dot_git))
		die(_("could not close file %s"), sb.buf);
	strbuf_reset(&sb);
	strbuf_reset(&rel_path);

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
