static ssize_t
archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
{
	int ret;
	struct zip *zip = a->format_data;

	if ((int64_t)s > zip->entry_uncompressed_limit)
		s = (size_t)zip->entry_uncompressed_limit;
	zip->entry_uncompressed_written += s;

	if (s == 0) return 0;

	switch (zip->entry_compression) {
	case COMPRESSION_STORE:
		ret = __archive_write_output(a, buff, s);
		if (ret != ARCHIVE_OK)
			return (ret);
		zip->written_bytes += s;
		zip->entry_compressed_written += s;
		break;
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
				zip->entry_compressed_written += zip->len_buf;
				zip->written_bytes += zip->len_buf;
				zip->stream.next_out = zip->buf;
				zip->stream.avail_out = (uInt)zip->len_buf;
			}
		} while (zip->stream.avail_in != 0);
		break;
#endif

	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid ZIP compression type");
		return ARCHIVE_FATAL;
	}

	zip->entry_uncompressed_limit -= s;
	zip->entry_crc32 = zip->crc32func(zip->entry_crc32, buff, (unsigned)s);
	return (s);

}