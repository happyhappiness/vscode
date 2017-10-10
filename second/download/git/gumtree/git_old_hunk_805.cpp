	}
	sq_quote_buf(&env, text);
	setenv(CONFIG_DATA_ENVIRONMENT, env.buf, 1);
	strbuf_release(&env);
}

int git_config_parse_parameter(const char *text,
			       config_fn_t fn, void *data)
{
	const char *value;
	struct strbuf **pair;

	pair = strbuf_split_str(text, '=', 2);
	if (!pair[0])
		return error("bogus config parameter: %s", text);

	if (pair[0]->len && pair[0]->buf[pair[0]->len - 1] == '=') {
