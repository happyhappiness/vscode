	return (ARCHIVE_OK);

#else

	archive_set_error(_a, ARCHIVE_ERRNO_MISC,

	    "Using external gzip program");

	return (ARCHIVE_WARN);

#endif

}

