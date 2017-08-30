		/* disk_start = archive_le16dec(p + 34); */ /* Better be zero. */
		/* internal_attributes = archive_le16dec(p + 36); */ /* text bit */
		external_attributes = archive_le32dec(p + 38);
		zip_entry->local_header_offset = archive_le32dec(p + 42);

		if (zip_entry->system == 3) {
			zip_entry->mode = external_attributes >> 16;
		} else {
			zip_entry->mode = AE_IFREG | 0777;
		}

		/* Do we need to parse filename here? */
		/* Or can we wait until we read the local header? */
		__archive_read_consume(a,
		    46 + filename_length + extra_length + comment_length);
	}

	/* TODO: Sort zip entries. */

	return ARCHIVE_OK;
}

static int
archive_read_format_zip_seekable_read_header(struct archive_read *a,
	struct archive_entry *entry)
{
	struct zip *zip = (struct zip *)a->format->data;
	int r;

	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
	if (a->archive.archive_format_name == NULL)
