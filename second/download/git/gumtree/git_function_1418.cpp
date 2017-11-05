static int ask_each_cmd(void)
{
	struct strbuf confirm = STRBUF_INIT;
	struct strbuf buf = STRBUF_INIT;
	struct string_list_item *item;
	const char *qname;
	int changed = 0, eof = 0;

	for_each_string_list_item(item, &del_list) {
		/* Ctrl-D should stop removing files */
		if (!eof) {
			qname = quote_path_relative(item->string, NULL, &buf);
			printf(_("remove %s? "), qname);
			if (strbuf_getline(&confirm, stdin, '\n') != EOF) {
				strbuf_trim(&confirm);
			} else {
				putchar('\n');
				eof = 1;
			}
		}
		if (!confirm.len || strncasecmp(confirm.buf, "yes", confirm.len)) {
			*item->string = '\0';
			changed++;
		}
	}

	if (changed)
		string_list_remove_empty_items(&del_list, 0);

	strbuf_release(&buf);
	strbuf_release(&confirm);
	return MENU_RETURN_NO_LOOP;
}