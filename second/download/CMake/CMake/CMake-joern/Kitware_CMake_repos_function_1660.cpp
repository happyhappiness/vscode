static const void *
cab_read_ahead_cfdata_deflate(struct archive_read *a, ssize_t *avail)
{
	*avail = ARCHIVE_FATAL;
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "libarchive compiled without deflate support (no libz)");
	return (NULL);
}