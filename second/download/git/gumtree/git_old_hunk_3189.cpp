	struct commit *commit = NULL;

	if (file_exists(path) && !is_empty_dir(path))
		die(_("'%s' already exists"), path);

	/* is 'refname' a branch or commit? */
	if (opts->force_new_branch) /* definitely a branch */
		;
	else if (!opts->detach && !strbuf_check_branch_ref(&symref, refname) &&
		 ref_exists(symref.buf)) { /* it's a branch */
		if (!opts->force)
			die_if_checked_out(symref.buf);
	} else { /* must be a commit */
		commit = lookup_commit_reference_by_name(refname);
		if (!commit)
