int mks_tempfile_sm(struct tempfile *tempfile,
		    const char *template, int suffixlen, int mode)
{
	prepare_tempfile_object(tempfile);

	strbuf_add_absolute_path(&tempfile->filename, template);
	tempfile->fd = git_mkstemps_mode(tempfile->filename.buf, suffixlen, mode);
	if (tempfile->fd < 0) {
		strbuf_reset(&tempfile->filename);
		return -1;
	}
	tempfile->owner = getpid();
	tempfile->active = 1;
	return tempfile->fd;
}