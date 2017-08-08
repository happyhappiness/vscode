{
	*avail = ARCHIVE_FATAL;
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "libarchive compiled without deflate support (no libz)");
	return (NULL);
}