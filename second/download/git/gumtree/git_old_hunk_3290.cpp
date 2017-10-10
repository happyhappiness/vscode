		strbuf_addf(&sb, "%s/index", sm_gitdir);
		unlink_or_warn(sb.buf);
		strbuf_reset(&sb);
	}

	/* Write a .git file in the submodule to redirect to the superproject. */
	if (safe_create_leading_directories_const(path) < 0)
		die(_("could not create directory '%s'"), path);

	if (path && *path)
		strbuf_addf(&sb, "%s/.git", path);
	else
		strbuf_addstr(&sb, ".git");

	if (safe_create_leading_directories_const(sb.buf) < 0)
		die(_("could not create leading directories of '%s'"), sb.buf);
	submodule_dot_git = fopen(sb.buf, "w");
	if (!submodule_dot_git)
		die_errno(_("cannot open file '%s'"), sb.buf);

	fprintf(submodule_dot_git, "gitdir: %s\n",
		relative_path(sm_gitdir, path, &rel_path));
	if (fclose(submodule_dot_git))
		die(_("could not close file %s"), sb.buf);
	strbuf_reset(&sb);
	strbuf_reset(&rel_path);

	cwd = xgetcwd();
	/* Redirect the worktree of the submodule in the superproject's config */
	if (!is_absolute_path(sm_gitdir)) {
		strbuf_addf(&sb, "%s/%s", cwd, sm_gitdir);
		free(sm_gitdir);
		sm_gitdir = strbuf_detach(&sb, NULL);
	}

	strbuf_addf(&sb, "%s/%s", cwd, path);
	p = git_pathdup_submodule(path, "config");
	if (!p)
		die(_("could not get submodule directory for '%s'"), path);
	git_config_set_in_file(p, "core.worktree",
			       relative_path(sb.buf, sm_gitdir, &rel_path));
	strbuf_release(&sb);
	strbuf_release(&rel_path);
	free(sm_gitdir);
	free(cwd);
	free(p);
	return 0;
}

struct cmd_struct {
	const char *cmd;
