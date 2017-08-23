ssize_t
archive_write_data_block(struct archive *a, const void *buff, size_t s, int64_t o)
{
	if (a->vtable->archive_write_data_block == NULL) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "archive_write_data_block not supported");
		a->state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	return ((a->vtable->archive_write_data_block)(a, buff, s, o));
}