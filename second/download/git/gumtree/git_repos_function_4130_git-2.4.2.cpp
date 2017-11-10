static int format_config(struct strbuf *buf, const char *key_, const char *value_)
{
	int must_free_vptr = 0;
	int must_print_delim = 0;
	char value[256];
	const char *vptr = value;

	strbuf_init(buf, 0);

	if (show_keys) {
		strbuf_addstr(buf, key_);
		must_print_delim = 1;
	}
	if (types == TYPE_INT)
		sprintf(value, "%"PRId64,
			git_config_int64(key_, value_ ? value_ : ""));
	else if (types == TYPE_BOOL)
		vptr = git_config_bool(key_, value_) ? "true" : "false";
	else if (types == TYPE_BOOL_OR_INT) {
		int is_bool, v;
		v = git_config_bool_or_int(key_, value_, &is_bool);
		if (is_bool)
			vptr = v ? "true" : "false";
		else
			sprintf(value, "%d", v);
	} else if (types == TYPE_PATH) {
		if (git_config_pathname(&vptr, key_, value_) < 0)
			return -1;
		must_free_vptr = 1;
	} else if (value_) {
		vptr = value_;
	} else {
		/* Just show the key name */
		vptr = "";
		must_print_delim = 0;
	}

	if (must_print_delim)
		strbuf_addch(buf, key_delim);
	strbuf_addstr(buf, vptr);
	strbuf_addch(buf, term);

	if (must_free_vptr)
		free((char *)vptr);
	return 0;
}