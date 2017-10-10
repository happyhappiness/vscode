	}
	if (process_path(path))
		die("Unable to process path %s", path);
	report("add '%s'", path);
}

static void read_index_info(int nul_term_line)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf uq = STRBUF_INIT;
	strbuf_getline_fn getline_fn;

	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
	while (getline_fn(&buf, stdin) != EOF) {
		char *ptr, *tab;
		char *path_name;
		unsigned char sha1[20];
		unsigned int mode;
		unsigned long ul;
		int stage;
