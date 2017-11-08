int mks_tempfile_tsm(struct tempfile *tempfile,
		     const char *template, int suffixlen, int mode)
{
	const char *tmpdir;

	prepare_tempfile_object(tempfile);

	tmpdir = getenv("TMPDIR");
	if (!tmpdir)
		tmpdir = "/tmp";

	strbuf_addf(&tempfile->filename, "%s/%s", tmpdir, template);
	tempfile->fd = git_mkstemps_mode(tempfile->filename.buf, suffixlen, mode);
	if (tempfile->fd < 0) {
		strbuf_reset(&tempfile->filename);
		return -1;
	}
	tempfile->owner = getpid();
	tempfile->active = 1;
	return tempfile->fd;
}