{
	int err, err2;

	err = read_body_to_string(a, tar, &(tar->pax_header), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);

	/* Parse the next header. */
	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);

	/*
	 * TODO: Parse global/default options into 'entry' struct here
	 * before handling file-specific options.
	 *
	 * This design (parse standard header, then overwrite with pax
	 * extended attribute data) usually works well, but isn't ideal;
	 * it would be better to parse the pax extended attributes first
	 * and then skip any fields in the standard header that were
	 * defined in the pax header.
	 */
	err2 = pax_header(a, tar, entry, &tar->pax_header);
	err =  err_combine(err, err2);
	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);
	return (err);
}