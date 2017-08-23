static int
archive_read_format_cab_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	struct cab *cab = (struct cab *)(a->format->data);
	int r;

	switch (cab->entry_cffile->folder) {
	case iFoldCONTINUED_FROM_PREV:
	case iFoldCONTINUED_TO_NEXT:
	case iFoldCONTINUED_PREV_AND_NEXT:
		*buff = NULL;
		*size = 0;
		*offset = 0;
		archive_clear_error(&a->archive);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Cannot restore this file split in multivolume.");
		return (ARCHIVE_FAILED);
	default:
		break;
	}
	if (cab->read_data_invoked == 0) {
		if (cab->bytes_skipped) {
			if (cab->entry_cfdata == NULL) {
				r = cab_next_cfdata(a);
				if (r < 0)
					return (r);
			}
			if (cab_consume_cfdata(a, cab->bytes_skipped) < 0)
				return (ARCHIVE_FATAL);
			cab->bytes_skipped = 0;
		}
		cab->read_data_invoked = 1;
	}
	if (cab->entry_unconsumed) {
		/* Consume as much as the compressor actually used. */
		r = (int)cab_consume_cfdata(a, cab->entry_unconsumed);
		cab->entry_unconsumed = 0;
		if (r < 0)
			return (r);
	}
	if (cab->end_of_archive || cab->end_of_entry) {
		if (!cab->end_of_entry_cleanup) {
			/* End-of-entry cleanup done. */
			cab->end_of_entry_cleanup = 1;
		}
		*offset = cab->entry_offset;
		*size = 0;
		*buff = NULL;
		return (ARCHIVE_EOF);
	}

	return (cab_read_data(a, buff, size, offset));
}