static GIT_PATH_FUNC(git_path_bisect_terms, "BISECT_TERMS")

static void read_bisect_paths(struct argv_array *array)
{
	struct strbuf str = STRBUF_INIT;
	const char *filename = git_path_bisect_names();
	FILE *fp = fopen(filename, "r");

	if (!fp)
		die_errno(_("Could not open file '%s'"), filename);

	while (strbuf_getline_lf(&str, fp) != EOF) {
		strbuf_trim(&str);
		if (sq_dequote_to_argv_array(str.buf, array))
			die(_("Badly quoted content in file '%s': %s"),
			    filename, str.buf);
