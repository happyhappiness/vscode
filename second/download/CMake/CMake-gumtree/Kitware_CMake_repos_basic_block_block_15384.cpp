{
	struct _7zip *zip;
	ssize_t bytes;

	zip = (struct _7zip *)a->format_data;

	if (s > zip->entry_bytes_remaining)
		s = (size_t)zip->entry_bytes_remaining;
	if (s == 0 || zip->cur_file == NULL)
		return (0);
	bytes = compress_out(a, buff, s, ARCHIVE_Z_RUN);
	if (bytes < 0)
		return (bytes);
	zip->entry_crc32 = crc32(zip->entry_crc32, buff, (unsigned)bytes);
	zip->entry_bytes_remaining -= bytes;
	return (bytes);
}