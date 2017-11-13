static int read_populate_todo(struct todo_list *todo_list,
			struct replay_opts *opts)
{
	const char *todo_file = get_todo_path(opts);
	int fd, res;

	strbuf_reset(&todo_list->buf);
	fd = open(todo_file, O_RDONLY);
	if (fd < 0)
		return error_errno(_("could not open '%s'"), todo_file);
	if (strbuf_read(&todo_list->buf, fd, 0) < 0) {
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

		for (i = 0; i < todo_list->nr; i++)
			if (valid == todo_list->items[i].command)
				continue;
			else if (valid == TODO_PICK)
				return error(_("cannot cherry-pick during a revert."));
			else
				return error(_("cannot revert during a cherry-pick."));
	}

	if (is_rebase_i(opts)) {
		struct todo_list done = TODO_LIST_INIT;
		FILE *f = fopen(rebase_path_msgtotal(), "w");

		if (strbuf_read_file(&done.buf, rebase_path_done(), 0) > 0 &&
				!parse_insn_buffer(done.buf.buf, &done))
			todo_list->done_nr = count_commands(&done);
		else
			todo_list->done_nr = 0;

		todo_list->total_nr = todo_list->done_nr
			+ count_commands(todo_list);
		todo_list_release(&done);

		if (f) {
			fprintf(f, "%d\n", todo_list->total_nr);
			fclose(f);
		}
	}

	return 0;
}