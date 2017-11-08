static void prepare_tempfile_object(struct tempfile *tempfile)
{
	if (!tempfile_list) {
		/* One-time initialization */
		sigchain_push_common(remove_tempfiles_on_signal);
		atexit(remove_tempfiles_on_exit);
	}

	if (tempfile->active)
		die("BUG: prepare_tempfile_object called for active object");
	if (!tempfile->on_list) {
		/* Initialize *tempfile and add it to tempfile_list: */
		tempfile->fd = -1;
		tempfile->fp = NULL;
		tempfile->active = 0;
		tempfile->owner = 0;
		strbuf_init(&tempfile->filename, 0);
		tempfile->next = tempfile_list;
		tempfile_list = tempfile;
		tempfile->on_list = 1;
	} else if (tempfile->filename.len) {
		/* This shouldn't happen, but better safe than sorry. */
		die("BUG: prepare_tempfile_object called for improperly-reset object");
	}
}