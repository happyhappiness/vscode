{
	struct archive_write *a = (struct archive_write *)_a;

	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "Xar not supported on this platform");
	return (ARCHIVE_WARN);
}