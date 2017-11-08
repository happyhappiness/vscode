int get_tempfile_fd(struct tempfile *tempfile)
{
	if (!tempfile->active)
		die("BUG: get_tempfile_fd() called for inactive object");
	return tempfile->fd;
}