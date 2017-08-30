	return (ARCHIVE_OK);

#else

	archive_set_error(_a, ARCHIVE_ERRNO_MISC,

	    "Using external gunzip program");

	return (ARCHIVE_WARN);

#endif

}

