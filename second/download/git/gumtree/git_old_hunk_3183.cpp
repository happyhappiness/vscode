	}
	if (process_path(path))
		die("Unable to process path %s", path);
	report("add '%s'", path);
}

static void read_index_info(int line_termination)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf uq = STRBUF_INIT;

	while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
		char *ptr, *tab;
		char *path_name;
		unsigned char sha1[20];
		unsigned int mode;
		unsigned long ul;
		int stage;
