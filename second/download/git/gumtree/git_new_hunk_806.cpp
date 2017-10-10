
	strbuf_trim(pair[0]);
	if (!pair[0]->len) {
		strbuf_list_free(pair);
		return error("bogus config parameter: %s", text);
	}

	if (git_config_parse_key(pair[0]->buf, &canonical_name, NULL)) {
		ret = -1;
	} else {
		ret = (fn(canonical_name, value, data) < 0) ? -1 : 0;
		free(canonical_name);
	}
	strbuf_list_free(pair);
	return ret;
}

int git_config_from_parameters(config_fn_t fn, void *data)
{
	const char *env = getenv(CONFIG_DATA_ENVIRONMENT);
	int ret = 0;
