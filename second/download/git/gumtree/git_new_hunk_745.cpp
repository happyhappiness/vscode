		close(fd);
		return error(_("could not read '%s'."), todo_file);
	}
	close(fd);

	res = parse_insn_buffer(todo_list->buf.buf, todo_list);
	if (res) {
		if (is_rebase_i(opts))
			return error(_("please fix this using "
				       "'git rebase --edit-todo'."));
		return error(_("unusable instruction sheet: '%s'"), todo_file);
	}

	if (!todo_list->nr &&
	    (!is_rebase_i(opts) || !file_exists(rebase_path_done())))
		return error(_("no commits parsed."));

	if (!is_rebase_i(opts)) {
		enum todo_command valid =
			opts->action == REPLAY_PICK ? TODO_PICK : TODO_REVERT;
		int i;

