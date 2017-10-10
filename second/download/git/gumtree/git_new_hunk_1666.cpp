
	if (args->verbose)
		fprintf(stderr, "%.*s\n", (int)path.len, path.buf);
	return write_entry(args, sha1, path.buf, path.len, mode);
}

static void queue_directory(const unsigned char *sha1,
		const char *base, int baselen, const char *filename,
		unsigned mode, int stage, struct archiver_context *c)
{
	struct directory *d;
	d = xmallocz(sizeof(*d) + baselen + 1 + strlen(filename));
	d->up	   = c->bottom;
	d->baselen = baselen;
	d->mode	   = mode;
	d->stage   = stage;
	c->bottom  = d;
	d->len = sprintf(d->path, "%.*s%s/", baselen, base, filename);
	hashcpy(d->sha1, sha1);
}

static int write_directory(struct archiver_context *c)
{
	struct directory *d = c->bottom;
	int ret;

	if (!d)
		return 0;
	c->bottom = d->up;
	d->path[d->len - 1] = '\0'; /* no trailing slash */
	ret =
		write_directory(c) ||
		write_archive_entry(d->sha1, d->path, d->baselen,
				    d->path + d->baselen, d->mode,
				    d->stage, c) != READ_TREE_RECURSIVE;
	free(d);
	return ret ? -1 : 0;
}

static int queue_or_write_archive_entry(const unsigned char *sha1,
		const char *base, int baselen, const char *filename,
		unsigned mode, int stage, void *context)
{
	struct archiver_context *c = context;

	while (c->bottom &&
	       !(baselen >= c->bottom->len &&
		 !strncmp(base, c->bottom->path, c->bottom->len))) {
		struct directory *next = c->bottom->up;
		free(c->bottom);
		c->bottom = next;
	}

	if (S_ISDIR(mode)) {
		queue_directory(sha1, base, baselen, filename,
				mode, stage, c);
		return READ_TREE_RECURSIVE;
	}

	if (write_directory(c))
		return -1;
	return write_archive_entry(sha1, base, baselen, filename, mode,
				   stage, context);
}

int write_archive_entries(struct archiver_args *args,
		write_archive_entry_fn_t write_entry)
{
	struct archiver_context context;
	struct unpack_trees_options opts;
	struct tree_desc t;
