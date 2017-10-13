const char *fast_export_read_path(const char *path, uint32_t *mode_out)
{
	int err;
	static struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	err = fast_export_ls(path, mode_out, &buf);
	if (err) {
		if (errno != ENOENT)
			die_errno("BUG: unexpected fast_export_ls error");
		/* Treat missing paths as directories. */
		*mode_out = S_IFDIR;
		return NULL;
	}
	return buf.buf;
}