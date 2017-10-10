struct archiver_context {
	struct archiver_args *args;
	write_archive_entry_fn_t write_entry;
	struct directory *bottom;
};

static int write_archive_entry(const unsigned char *sha1, const char *base,
		int baselen, const char *filename, unsigned mode, int stage,
		void *context)
{
	static struct strbuf path = STRBUF_INIT;
	static struct attr_check *check;
	struct archiver_context *c = context;
	struct archiver_args *args = c->args;
	write_archive_entry_fn_t write_entry = c->write_entry;
	const char *path_without_prefix;
	int err;

	args->convert = 0;
	strbuf_reset(&path);
	strbuf_grow(&path, PATH_MAX);
	strbuf_add(&path, args->base, args->baselen);
	strbuf_add(&path, base, baselen);
	strbuf_addstr(&path, filename);
	if (S_ISDIR(mode) || S_ISGITLINK(mode))
		strbuf_addch(&path, '/');
	path_without_prefix = path.buf + args->baselen;

	if (!check)
		check = attr_check_initl("export-ignore", "export-subst", NULL);
	if (!git_check_attr(path_without_prefix, check)) {
		if (ATTR_TRUE(check->items[0].value))
			return 0;
		args->convert = ATTR_TRUE(check->items[1].value);
	}

	if (S_ISDIR(mode) || S_ISGITLINK(mode)) {
		if (args->verbose)
			fprintf(stderr, "%.*s\n", (int)path.len, path.buf);
		err = write_entry(args, sha1, path.buf, path.len, mode);
