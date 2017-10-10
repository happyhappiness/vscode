	strbuf_release(&env);
}

int git_config_parse_parameter(const char *text,
			       config_fn_t fn, void *data)
{
	struct strbuf **pair;
	pair = strbuf_split_str(text, '=', 2);
	if (!pair[0])
		return error("bogus config parameter: %s", text);
	if (pair[0]->len && pair[0]->buf[pair[0]->len - 1] == '=')
		strbuf_setlen(pair[0], pair[0]->len - 1);
	strbuf_trim(pair[0]);
	if (!pair[0]->len) {
		strbuf_list_free(pair);
		return error("bogus config parameter: %s", text);
	}
	strbuf_tolower(pair[0]);
	if (fn(pair[0]->buf, pair[1] ? pair[1]->buf : NULL, data) < 0) {
		strbuf_list_free(pair);
		return -1;
	}
	strbuf_list_free(pair);
	return 0;
}
