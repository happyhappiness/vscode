int reopen_tempfile(struct tempfile *tempfile)
{
	if (0 <= tempfile->fd)
		die("BUG: reopen_tempfile called for an open object");
	if (!tempfile->active)
		die("BUG: reopen_tempfile called for an inactive object");
	tempfile->fd = open(tempfile->filename.buf, O_WRONLY);
	return tempfile->fd;
}