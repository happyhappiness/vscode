FILE *fdopen_tempfile(struct tempfile *tempfile, const char *mode)
{
	if (!tempfile->active)
		die("BUG: fdopen_tempfile() called for inactive object");
	if (tempfile->fp)
		die("BUG: fdopen_tempfile() called for open object");

	tempfile->fp = fdopen(tempfile->fd, mode);
	return tempfile->fp;
}