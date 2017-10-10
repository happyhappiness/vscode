			die(_("could not create directory '%s'"), path);
		strbuf_addf(&sb, "%s/index", sm_gitdir);
		unlink_or_warn(sb.buf);
		strbuf_reset(&sb);
	}

	/* Connect module worktree and git dir */
	connect_work_tree_and_git_dir(path, sm_gitdir);

	p = git_pathdup_submodule(path, "config");
	if (!p)
		die(_("could not get submodule directory for '%s'"), path);

	/* setup alternateLocation and alternateErrorStrategy in the cloned submodule if needed */
	git_config_get_string("submodule.alternateLocation", &sm_alternate);
	if (sm_alternate)
		git_config_set_in_file(p, "submodule.alternateLocation",
					   sm_alternate);
