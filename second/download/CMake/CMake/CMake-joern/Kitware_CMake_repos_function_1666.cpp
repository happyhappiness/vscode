static int
cab_read_data(struct archive_read *a, const void **buff,
    size_t *size, int64_t *offset)
{
	struct cab *cab = (struct cab *)(a->format->data);
	ssize_t bytes_avail;

	if (cab->entry_bytes_remaining == 0) {
		*buff = NULL;
		*size = 0;
		*offset = cab->entry_offset;
		cab->end_of_entry = 1;
		return (ARCHIVE_OK);
	}

	*buff = cab_read_ahead_cfdata(a, &bytes_avail);
	if (bytes_avail <= 0) {
		*buff = NULL;
		*size = 0;
		*offset = 0;
		if (bytes_avail == 0 &&
		    cab->entry_cfdata->uncompressed_size == 0) {
			/* All of CFDATA in a folder has been handled. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT, "Invalid CFDATA");
			return (ARCHIVE_FATAL);
		} else
			return ((int)bytes_avail);
	}
	if (bytes_avail > cab->entry_bytes_remaining)
		bytes_avail = (ssize_t)cab->entry_bytes_remaining;

	*size = bytes_avail;
	*offset = cab->entry_offset;
	cab->entry_offset += bytes_avail;
	cab->entry_bytes_remaining -= bytes_avail;
	if (cab->entry_bytes_remaining == 0)
		cab->end_of_entry = 1;
	cab->entry_unconsumed = bytes_avail;
	if (cab->entry_cffolder->comptype == COMPTYPE_NONE) {
		/* Don't consume more than current entry used. */
		if (cab->entry_cfdata->unconsumed > cab->entry_unconsumed)
			cab->entry_cfdata->unconsumed = cab->entry_unconsumed;
	}
	return (ARCHIVE_OK);
}