	OPT_BIT(0, "bool-or-int", &types, N_("value is --bool or --int"), TYPE_BOOL_OR_INT),
	OPT_BIT(0, "path", &types, N_("value is a path (file or directory name)"), TYPE_PATH),
	OPT_GROUP(N_("Other")),
	OPT_BOOL('z', "null", &end_null, N_("terminate values with NUL byte")),
	OPT_BOOL(0, "name-only", &omit_values, N_("show variable names only")),
	OPT_BOOL(0, "includes", &respect_includes, N_("respect include directives on lookup")),
	OPT_BOOL(0, "show-origin", &show_origin, N_("show origin of config (file, standard input, blob, command line)")),
	OPT_END(),
};

static void check_argc(int argc, int min, int max) {
	if (argc >= min && argc <= max)
		return;
	error("wrong number of arguments");
	usage_with_options(builtin_config_usage, builtin_config_options);
}

static void show_config_origin(struct strbuf *buf)
{
	const char term = end_null ? '\0' : '\t';

	strbuf_addstr(buf, current_config_origin_type());
	strbuf_addch(buf, ':');
	if (end_null)
		strbuf_addstr(buf, current_config_name());
	else
		quote_c_style(current_config_name(), buf, NULL, 0);
	strbuf_addch(buf, term);
}

static int show_all_config(const char *key_, const char *value_, void *cb)
{
	if (show_origin) {
		struct strbuf buf = STRBUF_INIT;
		show_config_origin(&buf);
		/* Use fwrite as "buf" can contain \0's if "end_null" is set. */
		fwrite(buf.buf, 1, buf.len, stdout);
		strbuf_release(&buf);
	}
	if (!omit_values && value_)
		printf("%s%c%s%c", key_, delim, value_, term);
	else
		printf("%s%c", key_, term);
	return 0;
}
