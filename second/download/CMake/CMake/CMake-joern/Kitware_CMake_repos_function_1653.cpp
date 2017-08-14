static const void *
cab_read_ahead_cfdata(struct archive_read *a, ssize_t *avail)
{
	struct cab *cab = (struct cab *)(a->format->data);
	int err;

	err = cab_next_cfdata(a);
	if (err < ARCHIVE_OK) {
		*avail = err;
		return (NULL);
	}

	switch (cab->entry_cffolder->comptype) {
	case COMPTYPE_NONE:
		return (cab_read_ahead_cfdata_none(a, avail));
	case COMPTYPE_MSZIP:
		return (cab_read_ahead_cfdata_deflate(a, avail));
	case COMPTYPE_LZX:
		return (cab_read_ahead_cfdata_lzx(a, avail));
	default: /* Unsupported compression. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported CAB compression : %s",
		    cab->entry_cffolder->compname);
		*avail = ARCHIVE_FAILED;
		return (NULL);
	}
}