
		item = append_new_todo(todo_list);
		item->offset_in_buf = p - todo_list->buf.buf;
		if (parse_insn_line(item, p, eol)) {
			res = error(_("invalid line %d: %.*s"),
				i, (int)(eol - p), p);
			item->command = TODO_NOOP;
		}

		if (fixup_okay)
			; /* do nothing */
		else if (is_fixup(item->command))
			return error(_("cannot '%s' without a previous commit"),
				command_to_string(item->command));
		else if (!is_noop(item->command))
			fixup_okay = 1;
	}

	return res;
}

static int count_commands(struct todo_list *todo_list)
{
	int count = 0, i;

	for (i = 0; i < todo_list->nr; i++)
		if (todo_list->items[i].command != TODO_COMMENT)
			count++;

	return count;
}

static int read_populate_todo(struct todo_list *todo_list,
			struct replay_opts *opts)
{
	const char *todo_file = get_todo_path(opts);
	int fd, res;

