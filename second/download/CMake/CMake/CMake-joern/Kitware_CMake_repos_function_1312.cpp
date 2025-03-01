static int
read_children(struct archive_read *a, struct file_info *parent)
{
	struct iso9660 *iso9660;
	const unsigned char *b, *p;
	struct file_info *multi;
	size_t step, skip_size;

	iso9660 = (struct iso9660 *)(a->format->data);
	/* flush any remaining bytes from the last round to ensure
	 * we're positioned */
	if (iso9660->entry_bytes_unconsumed) {
		__archive_read_consume(a, iso9660->entry_bytes_unconsumed);
		iso9660->entry_bytes_unconsumed = 0;
	}
	if (iso9660->current_position > parent->offset) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Ignoring out-of-order directory (%s) %jd > %jd",
		    parent->name.s,
		    (intmax_t)iso9660->current_position,
		    (intmax_t)parent->offset);
		return (ARCHIVE_WARN);
	}
	if (parent->offset + parent->size > iso9660->volume_size) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Directory is beyond end-of-media: %s",
		    parent->name.s);
		return (ARCHIVE_WARN);
	}
	if (iso9660->current_position < parent->offset) {
		int64_t skipsize;

		skipsize = parent->offset - iso9660->current_position;
		skipsize = __archive_read_consume(a, skipsize);
		if (skipsize < 0)
			return ((int)skipsize);
		iso9660->current_position = parent->offset;
	}

	step = (size_t)(((parent->size + iso9660->logical_block_size -1) /
	    iso9660->logical_block_size) * iso9660->logical_block_size);
	b = __archive_read_ahead(a, step, NULL);
	if (b == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Failed to read full block when scanning "
		    "ISO9660 directory list");
		return (ARCHIVE_FATAL);
	}
	iso9660->current_position += step;
	multi = NULL;
	skip_size = step;
	while (step) {
		p = b;
		b += iso9660->logical_block_size;
		step -= iso9660->logical_block_size;
		for (; *p != 0 && p < b && p + *p <= b; p += *p) {
			struct file_info *child;

			/* N.B.: these special directory identifiers
			 * are 8 bit "values" even on a
			 * Joliet CD with UCS-2 (16bit) encoding.
			 */

			/* Skip '.' entry. */
			if (*(p + DR_name_len_offset) == 1
			    && *(p + DR_name_offset) == '\0')
				continue;
			/* Skip '..' entry. */
			if (*(p + DR_name_len_offset) == 1
			    && *(p + DR_name_offset) == '\001')
				continue;
			child = parse_file_info(a, parent, p);
			if (child == NULL) {
				__archive_read_consume(a, skip_size);
				return (ARCHIVE_FATAL);
			}
			if (child->cl_offset == 0 &&
			    (child->multi_extent || multi != NULL)) {
				struct content *con;

				if (multi == NULL) {
					multi = child;
					multi->contents.first = NULL;
					multi->contents.last =
					    &(multi->contents.first);
				}
				con = malloc(sizeof(struct content));
				if (con == NULL) {
					archive_set_error(
					    &a->archive, ENOMEM,
					    "No memory for multi extent");
					__archive_read_consume(a, skip_size);
					return (ARCHIVE_FATAL);
				}
				con->offset = child->offset;
				con->size = child->size;
				con->next = NULL;
				*multi->contents.last = con;
				multi->contents.last = &(con->next);
				if (multi == child) {
					if (add_entry(a, iso9660, child)
					    != ARCHIVE_OK)
						return (ARCHIVE_FATAL);
				} else {
					multi->size += child->size;
					if (!child->multi_extent)
						multi = NULL;
				}
			} else
				if (add_entry(a, iso9660, child) != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
		}
	}

	__archive_read_consume(a, skip_size);

	/* Read data which recorded by RRIP "CE" extension. */
	if (read_CE(a, iso9660) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	return (ARCHIVE_OK);
}