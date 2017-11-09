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
		write_archive_entry(d->oid.hash, d->path, d->baselen,
				    d->path + d->baselen, d->mode,
				    d->stage, c) != READ_TREE_RECURSIVE;
	free(d);
	return ret ? -1 : 0;
}