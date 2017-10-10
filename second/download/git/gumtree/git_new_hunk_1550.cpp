
	if (get_message(commit, &msg) != 0)
		return error(_("cannot get commit message for %s"),
			oid_to_hex(&commit->object.oid));

	if (opts->allow_ff && !is_fixup(command) &&
	    ((parent && !oidcmp(&parent->object.oid, &head)) ||
	     (!parent && unborn))) {
		if (is_rebase_i(opts))
			write_author_script(msg.message);
		res = fast_forward_to(&commit->object.oid, &head, unborn,
			opts);
		if (res || command != TODO_REWORD)
			goto leave;
		flags |= EDIT_MSG | AMEND_MSG;
		if (command == TODO_REWORD)
			flags |= VERIFY_MSG;
