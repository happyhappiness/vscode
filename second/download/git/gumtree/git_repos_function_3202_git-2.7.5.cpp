FILE *get_tempfile_fp(struct tempfile *tempfile)
{
	if (!tempfile->active)
		die("BUG: get_tempfile_fp() called for inactive object");
	return tempfile->fp;
}