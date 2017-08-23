int
archive_read_disk_set_standard_lookup(struct archive *a)
{
	archive_set_error(a, -1, "Standard lookups not available on Windows");
	return (ARCHIVE_FATAL);
}