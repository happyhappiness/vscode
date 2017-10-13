static int parse_insn_buffer(char *buf, struct todo_list *todo_list)
{
	struct todo_item *item;
	char *p = buf, *next_p;
	int i, res = 0;

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
			item->command = -1;
		}
	}
	if (!todo_list->nr)
		return error(_("no commits parsed."));
	return res;
}