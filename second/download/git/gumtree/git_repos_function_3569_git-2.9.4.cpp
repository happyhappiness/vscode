static int write_archive_entry_buf(const unsigned char *sha1, struct strbuf *base,
		const char *filename, unsigned mode, int stage,
		void *context)
{
	return write_archive_entry(sha1, base->buf, base->len,
				     filename, mode, stage, context);
}