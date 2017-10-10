
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
