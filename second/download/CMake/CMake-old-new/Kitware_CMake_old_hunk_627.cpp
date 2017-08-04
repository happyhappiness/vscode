	} else {
#ifdef HAVE_ZLIB_H
		struct zip *zip = a->format_data;
		zip->compression = COMPRESSION_DEFLATE;
		ret = ARCHIVE_OK;
#else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			"deflate compression not supported");
#endif
	}
	return (ret);
