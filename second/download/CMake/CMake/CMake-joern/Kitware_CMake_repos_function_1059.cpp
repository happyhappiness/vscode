static int
archive_write_raw_header(struct archive_write *a, struct archive_entry *entry)
{
	struct raw *raw = (struct raw *)a->format_data;

	if (archive_entry_filetype(entry) != AE_IFREG) {
		archive_set_error(&a->archive, ERANGE,
		    "Raw format only supports filetype AE_IFREG");
		return (ARCHIVE_FATAL);
	}


	if (raw->entries_written > 0) {
		archive_set_error(&a->archive, ERANGE,
		    "Raw format only supports one entry per archive");
		return (ARCHIVE_FATAL);
	}
	raw->entries_written++;

	return (ARCHIVE_OK);
}