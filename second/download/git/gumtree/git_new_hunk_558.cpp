	};

static const char *boolean_options[] = {
	TRANS_OPT_THIN,
	TRANS_OPT_KEEP,
	TRANS_OPT_FOLLOWTAGS,
	TRANS_OPT_DEEPEN_RELATIVE
	};

static int strbuf_set_helper_option(struct helper_data *data,
				    struct strbuf *buf)
{
	int ret;

	sendline(data, buf);
	if (recvline(data, buf))
		exit(128);

	if (!strcmp(buf->buf, "ok"))
		ret = 0;
	else if (starts_with(buf->buf, "error"))
		ret = -1;
	else if (!strcmp(buf->buf, "unsupported"))
		ret = 1;
	else {
		warning("%s unexpectedly said: '%s'", data->name, buf->buf);
		ret = 1;
	}
	return ret;
}

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

static int set_helper_option(struct transport *transport,
			  const char *name, const char *value)
{
	struct helper_data *data = transport->data;
	struct strbuf buf = STRBUF_INIT;
	int i, ret, is_bool = 0;

	get_helper(transport);

	if (!data->option)
		return 1;

	if (!strcmp(name, "deepen-not"))
		return string_list_set_helper_option(data, name,
						     (struct string_list *)value);

	for (i = 0; i < ARRAY_SIZE(unsupported_options); i++) {
		if (!strcmp(name, unsupported_options[i]))
			return 1;
	}

	for (i = 0; i < ARRAY_SIZE(boolean_options); i++) {
