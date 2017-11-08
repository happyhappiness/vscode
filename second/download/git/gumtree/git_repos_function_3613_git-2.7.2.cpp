static int fill_textconv_grep(struct userdiff_driver *driver,
			      struct grep_source *gs)
{
	struct diff_filespec *df;
	char *buf;
	size_t size;

	if (!driver || !driver->textconv)
		return grep_source_load(gs);

	/*
	 * The textconv interface is intimately tied to diff_filespecs, so we
	 * have to pretend to be one. If we could unify the grep_source
	 * and diff_filespec structs, this mess could just go away.
	 */
	df = alloc_filespec(gs->path);
	switch (gs->type) {
	case GREP_SOURCE_SHA1:
		fill_filespec(df, gs->identifier, 1, 0100644);
		break;
	case GREP_SOURCE_FILE:
		fill_filespec(df, null_sha1, 0, 0100644);
		break;
	default:
		die("BUG: attempt to textconv something without a path?");
	}

	/*
	 * fill_textconv is not remotely thread-safe; it may load objects
	 * behind the scenes, and it modifies the global diff tempfile
	 * structure.
	 */
	grep_read_lock();
	size = fill_textconv(driver, df, &buf);
	grep_read_unlock();
	free_filespec(df);

	/*
	 * The normal fill_textconv usage by the diff machinery would just keep
	 * the textconv'd buf separate from the diff_filespec. But much of the
	 * grep code passes around a grep_source and assumes that its "buf"
	 * pointer is the beginning of the thing we are searching. So let's
	 * install our textconv'd version into the grep_source, taking care not
	 * to leak any existing buffer.
	 */
	grep_source_clear_data(gs);
	gs->buf = buf;
	gs->size = size;

	return 0;
}