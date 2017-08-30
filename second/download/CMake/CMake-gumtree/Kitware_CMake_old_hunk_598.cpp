
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
