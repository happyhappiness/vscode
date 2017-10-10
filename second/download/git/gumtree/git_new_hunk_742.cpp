	} else if (0 < opts->mainline)
		return error(_("mainline was specified but commit %s is not a merge."),
			oid_to_hex(&commit->object.oid));
	else
		parent = commit->parents->item;

	if (get_message(commit, &msg) != 0)
		return error(_("cannot get commit message for %s"),
			oid_to_hex(&commit->object.oid));

	if (opts->allow_ff && !is_fixup(command) &&
	    ((parent && !hashcmp(parent->object.oid.hash, head)) ||
	     (!parent && unborn))) {
		if (is_rebase_i(opts))
			write_author_script(msg.message);
		res = fast_forward_to(commit->object.oid.hash, head, unborn,
			opts);
		if (res || command != TODO_REWORD)
			goto leave;
		edit = amend = 1;
		msg_file = NULL;
		goto fast_forward_edit;
	}
	if (parent && parse_commit(parent) < 0)
		/* TRANSLATORS: The first %s will be a "todo" command like
		   "revert" or "pick", the second %s a SHA1. */
		return error(_("%s: cannot parse parent commit %s"),
			command_to_string(command),
			oid_to_hex(&parent->object.oid));

	/*
	 * "commit" is an existing commit.  We would want to apply
	 * the difference it introduces since its first parent "prev"
	 * on top of the current HEAD if we are cherry-pick.  Or the
	 * reverse of it if we are revert.
	 */
