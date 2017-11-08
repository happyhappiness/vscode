static int format_config(struct strbuf *buf, const char *key_, const char *value_)
{
	if (show_origin)
		show_config_origin(buf);
	if (show_keys)
		strbuf_addstr(buf, key_);
	if (!omit_values) {
		if (show_keys)
			strbuf_addch(buf, key_delim);

		if (types == TYPE_INT)
			strbuf_addf(buf, "%"PRId64,
				    git_config_int64(key_, value_ ? value_ : ""));
		else if (types == TYPE_BOOL)
			strbuf_addstr(buf, git_config_bool(key_, value_) ?
				      "true" : "false");
		else if (types == TYPE_BOOL_OR_INT) {
			int is_bool, v;
			v = git_config_bool_or_int(key_, value_, &is_bool);
			if (is_bool)
				strbuf_addstr(buf, v ? "true" : "false");
			else
				strbuf_addf(buf, "%d", v);
		} else if (types == TYPE_PATH) {
			const char *v;
			if (git_config_pathname(&v, key_, value_) < 0)
				return -1;
			strbuf_addstr(buf, v);
			free((char *)v);
		} else if (value_) {
			strbuf_addstr(buf, value_);
		} else {
			/* Just show the key name; back out delimiter */
			if (show_keys)
				strbuf_setlen(buf, buf->len - 1);
		}
	}
	strbuf_addch(buf, term);
	return 0;
}