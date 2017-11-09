static int parse_insn_buffer(char *buf, struct todo_list *todo_list)
{
	struct todo_item *item;
	char *p = buf, *next_p;
	int i, res = 0, fixup_okay = file_exists(rebase_path_done());

	for (i = 1; *p; i++, p = next_p) {
		char *eol = strchrnul(p, '\n');

		next_p = *eol ? eol + 1 /* skip LF */ : eol;

		if (p != eol && eol[-1] == '\r')
			eol--; /* strip Carriage Return */

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