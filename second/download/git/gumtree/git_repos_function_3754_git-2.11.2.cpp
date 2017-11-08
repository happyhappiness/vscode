static int string_list_set_helper_option(struct helper_data *data,
					 const char *name,
					 struct string_list *list)
{
	struct strbuf buf = STRBUF_INIT;
	int i, ret = 0;

	for (i = 0; i < list->nr; i++) {
		strbuf_addf(&buf, "option %s ", name);
		quote_c_style(list->items[i].string, &buf, NULL, 0);
		strbuf_addch(&buf, '\n');

		if ((ret = strbuf_set_helper_option(data, &buf)))
			break;
		strbuf_reset(&buf);
	}
	strbuf_release(&buf);
	return ret;
}