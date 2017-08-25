static ssize_t
archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
{
	int ret;
	struct zip *zip = a->format_data;
	struct zip_file_header_link *l = zip->central_directory_end;

	if ((int64_t)s > zip->remaining_data_bytes)
		s = (size_t)zip->remaining_data_bytes;

	if (s == 0) return 0;

	switch (l->compression) {
	case COMPRESSION_STORE:
		ret = __archive_write_output(a, buff, s);
		if (ret != ARCHIVE_OK) return (ret);
		zip->written_bytes += s;
		zip->remaining_data_bytes -= s;
		l->compressed_size += s;
		l->crc32 = crc32(l->crc32, buff, (unsigned)s);
		return (s);
#if HAVE_ZLIB_H
	case COMPRESSION_DEFLATE:
		zip->stream.next_in = (unsigned char*)(uintptr_t)buff;
		zip->stream.avail_in = (uInt)s;
		do {
			ret = deflate(&zip->stream, Z_NO_FLUSH);
			if (ret == Z_STREAM_ERROR)
				return (ARCHIVE_FATAL);
			if (zip->stream.avail_out == 0) {
				ret = __archive_write_output(a, zip->buf,
					zip->len_buf);
				if (ret != ARCHIVE_OK)
					return (ret);
				l->compressed_size += zip->len_buf;
				zip->written_bytes += zip->len_buf;
				zip->stream.next_out = zip->buf;
				zip->stream.avail_out = (uInt)zip->len_buf;
			}
		} while (zip->stream.avail_in != 0);
		zip->remaining_data_bytes -= s;
		/* If we have it, use zlib's fast crc32() */
		l->crc32 = crc32(l->crc32, buff, (uInt)s);
		return (s);
#endif

	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid ZIP compression type");
		return ARCHIVE_FATAL;
	}
}