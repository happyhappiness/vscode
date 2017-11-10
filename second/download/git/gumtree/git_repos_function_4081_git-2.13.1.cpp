static void queue_directory(const unsigned char *sha1,
		struct strbuf *base, const char *filename,
		unsigned mode, int stage, struct archiver_context *c)
{
	struct directory *d;
	size_t len = st_add4(base->len, 1, strlen(filename), 1);
	d = xmalloc(st_add(sizeof(*d), len));
	d->up	   = c->bottom;
	d->baselen = base->len;
	d->mode	   = mode;
	d->stage   = stage;
	c->bottom  = d;
	d->len = xsnprintf(d->path, len, "%.*s%s/", (int)base->len, base->buf, filename);
	hashcpy(d->oid.hash, sha1);
}