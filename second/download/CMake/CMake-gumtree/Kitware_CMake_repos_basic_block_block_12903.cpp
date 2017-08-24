{
	const struct archive_entry_header_gnutar *header;
	int64_t t;
	int err = ARCHIVE_OK;

	/*
	 * GNU header is like POSIX ustar, except 'prefix' is
	 * replaced with some other fields. This also means the
	 * filename is stored as in old-style archives.
	 */

	/* Grab fields common to all tar variants. */
	err = header_common(a, tar, entry, h);
	if (err == ARCHIVE_FATAL)
		return (err);

	/* Copy filename over (to ensure null termination). */
	header = (const struct archive_entry_header_gnutar *)h;
	if (archive_entry_copy_pathname_l(entry,
	    header->name, sizeof(header->name), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Pathname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Fields common to ustar and GNU */
	/* XXX Can the following be factored out since it's common
	 * to ustar and gnu tar?  Is it okay to move it down into
	 * header_common, perhaps?  */
	if (archive_entry_copy_uname_l(entry,
	    header->uname, sizeof(header->uname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Uname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	if (archive_entry_copy_gname_l(entry,
	    header->gname, sizeof(header->gname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Gname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Parse out device numbers only for char and block specials */
	if (header->typeflag[0] == '3' || header->typeflag[0] == '4') {
		archive_entry_set_rdevmajor(entry, (dev_t)
		    tar_atol(header->rdevmajor, sizeof(header->rdevmajor)));
		archive_entry_set_rdevminor(entry, (dev_t)
		    tar_atol(header->rdevminor, sizeof(header->rdevminor)));
	} else
		archive_entry_set_rdev(entry, 0);

	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);

	/* Grab GNU-specific fields. */
	t = tar_atol(header->atime, sizeof(header->atime));
	if (t > 0)
		archive_entry_set_atime(entry, t, 0);
	t = tar_atol(header->ctime, sizeof(header->ctime));
	if (t > 0)
		archive_entry_set_ctime(entry, t, 0);

	if (header->realsize[0] != 0) {
		tar->realsize
		    = tar_atol(header->realsize, sizeof(header->realsize));
		archive_entry_set_size(entry, tar->realsize);
	}

	if (header->sparse[0].offset[0] != 0) {
		if (gnu_sparse_old_read(a, tar, header, unconsumed)
		    != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	} else {
		if (header->isextended[0] != 0) {
			/* XXX WTF? XXX */
		}
	}

	return (err);
}