{
	int err;

	err = read_body_to_string(a, tar, &(tar->longname), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);
	/* Read and parse "real" header, then override name. */
	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);
	if (archive_entry_copy_pathname_l(entry, tar->longname.s,
	    archive_strlen(&(tar->longname)), tar->sconv) != 0)
		err = set_conversion_failed_error(a, tar->sconv, "Pathname");
	return (err);
}