	return (ARCHIVE_OK);

#else

	archive_set_error(_a, ARCHIVE_ERRNO_MISC,

	    "Using external lzma program for lzma decompression");

	return (ARCHIVE_WARN);

#endif

}

