int check_pager_config(const char *cmd)
{
	int want = -1;
	struct strbuf key = STRBUF_INIT;
	const char *value = NULL;
	strbuf_addf(&key, "pager.%s", cmd);
	if (git_config_key_is_valid(key.buf) &&
	    !git_config_get_value(key.buf, &value)) {
		int b = git_config_maybe_bool(key.buf, value);
		if (b >= 0)
			want = b;
		else {
			want = 1;
			pager_program = xstrdup(value);
		}
	}
	strbuf_release(&key);
	return want;
}