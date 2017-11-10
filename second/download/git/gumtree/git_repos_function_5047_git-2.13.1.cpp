static int get_urlmatch(const char *var, const char *url)
{
	int ret;
	char *section_tail;
	struct string_list_item *item;
	struct urlmatch_config config = { STRING_LIST_INIT_DUP };
	struct string_list values = STRING_LIST_INIT_DUP;

	config.collect_fn = urlmatch_collect_fn;
	config.cascade_fn = NULL;
	config.cb = &values;

	if (!url_normalize(url, &config.url))
		die("%s", config.url.err);

	config.section = xstrdup_tolower(var);
	section_tail = strchr(config.section, '.');
	if (section_tail) {
		*section_tail = '\0';
		config.key = section_tail + 1;
		show_keys = 0;
	} else {
		config.key = NULL;
		show_keys = 1;
	}

	git_config_with_options(urlmatch_config_entry, &config,
				&given_config_source, &config_options);

	ret = !values.nr;

	for_each_string_list_item(item, &values) {
		struct urlmatch_current_candidate_value *matched = item->util;
		struct strbuf buf = STRBUF_INIT;

		format_config(&buf, item->string,
			      matched->value_is_null ? NULL : matched->value.buf);
		fwrite(buf.buf, 1, buf.len, stdout);
		strbuf_release(&buf);

		strbuf_release(&matched->value);
	}
	string_list_clear(&config.vars, 1);
	string_list_clear(&values, 1);
	free(config.url.url);

	free((void *)config.section);
	return ret;
}