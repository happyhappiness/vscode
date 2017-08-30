	return (ARCHIVE_OK);
#else
	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
	    "Using external unxz program for xz decompression");
	return (ARCHIVE_WARN);
#endif
}
