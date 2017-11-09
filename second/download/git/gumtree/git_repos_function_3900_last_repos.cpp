int rename_tempfile(struct tempfile *tempfile, const char *path)
{
	if (!tempfile->active)
		die("BUG: rename_tempfile called for inactive object");

	if (close_tempfile(tempfile))
		return -1;

	if (rename(tempfile->filename.buf, path)) {
		int save_errno = errno;
		delete_tempfile(tempfile);
		errno = save_errno;
		return -1;
	}

	tempfile->active = 0;
	strbuf_reset(&tempfile->filename);
	return 0;
}