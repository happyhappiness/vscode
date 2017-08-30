	return (ARCHIVE_OK);

#else

	archive_set_error(_a, ARCHIVE_ERRNO_MISC,

	    "Using external bzip2 program");

	return (ARCHIVE_WARN);

#endif

}

