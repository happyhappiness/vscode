const char *get_tempfile_path(struct tempfile *tempfile)
{
	if (!tempfile->active)
		die("BUG: get_tempfile_path() called for inactive object");
	return tempfile->filename.buf;
}