	}
	strbuf_release(&buf);
	free(expanded);
	return ret;
}

int git_config_include(const char *var, const char *value, void *data)
{
	struct config_include_data *inc = data;
	int ret;

	/*
	 * Pass along all values, including "include" directives; this makes it
	 * possible to query information on the includes themselves.
	 */
	ret = inc->fn(var, value, inc->data);
	if (ret < 0)
		return ret;

	if (!strcmp(var, "include.path"))
		ret = handle_path_include(value, inc);
	return ret;
}

void git_config_push_parameter(const char *text)
{
	struct strbuf env = STRBUF_INIT;
