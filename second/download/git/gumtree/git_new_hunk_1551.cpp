			else
				return error(_("cannot revert during a cherry-pick."));
	}

	if (is_rebase_i(opts)) {
		struct todo_list done = TODO_LIST_INIT;
		FILE *f = fopen_or_warn(rebase_path_msgtotal(), "w");

		if (strbuf_read_file(&done.buf, rebase_path_done(), 0) > 0 &&
				!parse_insn_buffer(done.buf.buf, &done))
			todo_list->done_nr = count_commands(&done);
		else
			todo_list->done_nr = 0;
