static void queue_directory(const unsigned char *sha1,
		struct strbuf *base, const char *filename,
		unsigned mode, int stage, struct archiver_context *c)
{
	struct directory *d;
	d = xmallocz(sizeof(*d) + base->len + 1 + strlen(filename));
	d->up	   = c->bottom;
	d->baselen = base->len;
	d->mode	   = mode;
	d->stage   = stage;
	c->bottom  = d;
	d->len = sprintf(d->path, "%.*s%s/", (int)base->len, base->buf, filename);
	hashcpy(d->sha1, sha1);
}