{
	struct _7zip *zip;
	size_t s;
	ssize_t r;

	zip = (struct _7zip *)a->format_data;
	if (zip->cur_file == NULL)
		return (ARCHIVE_OK);

	while (zip->entry_bytes_remaining > 0) {
		s = (size_t)zip->entry_bytes_remaining;
		if (s > a->null_length)
			s = a->null_length;
		r = _7z_write_data(a, a->nulls, s);
		if (r < 0)
			return ((int)r);
	}
	zip->total_bytes_compressed += zip->stream.total_in;
	zip->total_bytes_uncompressed += zip->stream.total_out;
	zip->cur_file->crc32 = zip->entry_crc32;
	zip->cur_file = NULL;

	return (ARCHIVE_OK);
}