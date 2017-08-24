	size_t step, skip_size;

	iso9660 = (struct iso9660 *)(a->format->data);
	if (iso9660->current_position > parent->offset) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Ignoring out-of-order directory (%s) %jd > %jd",
