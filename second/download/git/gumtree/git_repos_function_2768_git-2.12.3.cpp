static int parse_insn_line(struct todo_item *item, const char *bol, char *eol)
{
	unsigned char commit_sha1[20];
	char *end_of_object_name;
	int i, saved, status, padding;

	/* left-trim */
	bol += strspn(bol, " \t");

	if (bol == eol || *bol == '\r' || *bol == comment_line_char) {
		item->command = TODO_COMMENT;
		item->commit = NULL;
		item->arg = bol;
		item->arg_len = eol - bol;
		return 0;
	}

	for (i = 0; i < TODO_COMMENT; i++)
		if (skip_prefix(bol, todo_command_info[i].str, &bol)) {
			item->command = i;
			break;
		} else if (bol[1] == ' ' && *bol == todo_command_info[i].c) {
			bol++;
			item->command = i;
			break;
		}
	if (i >= TODO_COMMENT)
		return -1;

	if (item->command == TODO_NOOP) {
		item->commit = NULL;
		item->arg = bol;
		item->arg_len = eol - bol;
		return 0;
	}

	/* Eat up extra spaces/ tabs before object name */
	padding = strspn(bol, " \t");
	if (!padding)
		return -1;
	bol += padding;

	if (item->command == TODO_EXEC) {
		item->arg = bol;
		item->arg_len = (int)(eol - bol);
		return 0;
	}

	end_of_object_name = (char *) bol + strcspn(bol, " \t\n");
	saved = *end_of_object_name;
	*end_of_object_name = '\0';
	status = get_sha1(bol, commit_sha1);
	*end_of_object_name = saved;

	item->arg = end_of_object_name + strspn(end_of_object_name, " \t");
	item->arg_len = (int)(eol - item->arg);

	if (status < 0)
		return -1;

	item->commit = lookup_commit_reference(commit_sha1);
	return !item->commit;
}