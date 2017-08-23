int
archive_write_add_filter_xz(struct archive *a)
{
	archive_set_error(a, ARCHIVE_ERRNO_MISC,
	    "xz compression not supported on this platform");
	return (ARCHIVE_FATAL);
}