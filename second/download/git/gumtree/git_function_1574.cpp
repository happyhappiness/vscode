void git_die_config(const char *key, const char *err, ...)
{
	const struct string_list *values;
	struct key_value_info *kv_info;

	if (err) {
		va_list params;
		va_start(params, err);
		vreportf("error: ", err, params);
		va_end(params);
	}
	values = git_config_get_value_multi(key);
	kv_info = values->items[values->nr - 1].util;
	git_die_config_linenr(key, kv_info->filename, kv_info->linenr);
}