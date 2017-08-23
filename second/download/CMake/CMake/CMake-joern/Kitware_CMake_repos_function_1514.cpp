static int
archive_write_ar_finish_entry(struct archive_write *a)
{
	struct ar_w *ar;
	int ret;

	ar = (struct ar_w *)a->format_data;

	if (ar->entry_bytes_remaining != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Entry remaining bytes larger than 0");
		return (ARCHIVE_WARN);
	}

	if (ar->entry_padding == 0) {
		return (ARCHIVE_OK);
	}

	if (ar->entry_padding != 1) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Padding wrong size: %ju should be 1 or 0",
		    (uintmax_t)ar->entry_padding);
		return (ARCHIVE_WARN);
	}

	ret = __archive_write_output(a, "\n", 1);
	return (ret);
}