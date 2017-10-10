
	strbuf_trim(pair[0]);
	if (!pair[0]->len) {
		strbuf_list_free(pair);
		return error("bogus config parameter: %s", text);
	}
	strbuf_tolower(pair[0]);
	if (fn(pair[0]->buf, value, data) < 0) {
		strbuf_list_free(pair);
		return -1;
	}
	strbuf_list_free(pair);
	return 0;
}

int git_config_from_parameters(config_fn_t fn, void *data)
{
	const char *env = getenv(CONFIG_DATA_ENVIRONMENT);
	int ret = 0;
