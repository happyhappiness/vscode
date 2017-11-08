void delete_tempfile(struct tempfile *tempfile)
{
	if (!tempfile->active)
		return;

	if (!close_tempfile(tempfile)) {
		unlink_or_warn(tempfile->filename.buf);
		tempfile->active = 0;
		strbuf_reset(&tempfile->filename);
	}
}