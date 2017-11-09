static int queue_or_write_archive_entry(const unsigned char *sha1,
		struct strbuf *base, const char *filename,
		unsigned mode, int stage, void *context)
{
	struct archiver_context *c = context;

	while (c->bottom &&
	       !(base->len >= c->bottom->len &&
		 !strncmp(base->buf, c->bottom->path, c->bottom->len))) {
		struct directory *next = c->bottom->up;
		free(c->bottom);
		c->bottom = next;
	}

	if (S_ISDIR(mode)) {
		size_t baselen = base->len;
		const struct attr_check *check;

		/* Borrow base, but restore its original value when done. */
		strbuf_addstr(base, filename);
		strbuf_addch(base, '/');
		check = get_archive_attrs(base->buf);
		strbuf_setlen(base, baselen);

		if (check_attr_export_ignore(check))
			return 0;
		queue_directory(sha1, base, filename,
				mode, stage, c);
		return READ_TREE_RECURSIVE;
	}

	if (write_directory(c))
		return -1;
	return write_archive_entry(sha1, base->buf, base->len, filename, mode,
				   stage, context);
}