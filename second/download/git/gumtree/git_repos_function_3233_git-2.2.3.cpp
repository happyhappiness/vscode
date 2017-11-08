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