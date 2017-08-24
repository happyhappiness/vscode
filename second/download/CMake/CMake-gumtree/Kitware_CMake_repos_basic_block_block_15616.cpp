{
	struct ar_w *ar;
	int ret;

	/*
	 * If we haven't written anything yet, we need to write
	 * the ar global header now to make it a valid ar archive.
	 */
	ar = (struct ar_w *)a->format_data;
	if (!ar->wrote_global_header) {
		ar->wrote_global_header = 1;
		ret = __archive_write_output(a, "!<arch>\n", 8);
		return (ret);
	}

	return (ARCHIVE_OK);
}