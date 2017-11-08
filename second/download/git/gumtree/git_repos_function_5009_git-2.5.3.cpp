static void pretty_print_dels(void)
{
	struct string_list list = STRING_LIST_INIT_DUP;
	struct string_list_item *item;
	struct strbuf buf = STRBUF_INIT;
	const char *qname;
	struct column_options copts;

	for_each_string_list_item(item, &del_list) {
		qname = quote_path_relative(item->string, NULL, &buf);
		string_list_append(&list, qname);
	}

	/*
	 * always enable column display, we only consult column.*
	 * about layout strategy and stuff
	 */
	colopts = (colopts & ~COL_ENABLE_MASK) | COL_ENABLED;
	memset(&copts, 0, sizeof(copts));
	copts.indent = "  ";
	copts.padding = 2;
	print_columns(&list, colopts, &copts);
	strbuf_release(&buf);
	string_list_clear(&list, 0);
}