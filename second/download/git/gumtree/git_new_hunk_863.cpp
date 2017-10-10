	OPT_BOOL(0 , "stdin", &stdin_paths, N_("read file names from stdin")),
	OPT_BOOL('z', NULL, &nul_term_line,
		 N_("terminate input and output records by a NUL character")),
	OPT_END()
};

static void output_attr(struct attr_check *check, const char *file)
{
	int j;
	int cnt = check->nr;

	for (j = 0; j < cnt; j++) {
		const char *value = check->items[j].value;

		if (ATTR_TRUE(value))
			value = "set";
		else if (ATTR_FALSE(value))
			value = "unset";
		else if (ATTR_UNSET(value))
			value = "unspecified";

		if (nul_term_line) {
			printf("%s%c" /* path */
			       "%s%c" /* attrname */
			       "%s%c" /* attrvalue */,
			       file, 0,
			       git_attr_name(check->items[j].attr), 0, value, 0);
		} else {
			quote_c_style(file, NULL, stdout, 0);
			printf(": %s: %s\n",
			       git_attr_name(check->items[j].attr), value);
		}
	}
}

static void check_attr(const char *prefix,
		       struct attr_check *check,
		       int collect_all,
		       const char *file)
{
	char *full_path =
		prefix_path(prefix, prefix ? strlen(prefix) : 0, file);

	if (collect_all) {
		git_all_attrs(full_path, check);
	} else {
		if (git_check_attr(full_path, check))
			die("git_check_attr died");
	}
	output_attr(check, file);

	free(full_path);
}

static void check_attr_stdin_paths(const char *prefix,
				   struct attr_check *check,
				   int collect_all)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf unquoted = STRBUF_INIT;
	strbuf_getline_fn getline_fn;

	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
