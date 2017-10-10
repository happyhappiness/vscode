		commit = lookup_commit_reference_by_name(refname);
		if (!commit)
			die(_("invalid reference: %s"), refname);
	}

	name = worktree_basename(path, &len);
	strbuf_addstr(&sb_repo,
		      git_path("worktrees/%.*s", (int)(path + len - name), name));
	len = sb_repo.len;
	if (safe_create_leading_directories_const(sb_repo.buf))
		die_errno(_("could not create leading directories of '%s'"),
			  sb_repo.buf);
	while (!stat(sb_repo.buf, &st)) {
		counter++;
