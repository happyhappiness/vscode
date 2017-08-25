int
__archive_read_program(struct archive_read_filter *self, const char *cmd)
{
	(void)self; /* UNUSED */
	(void)cmd; /* UNUSED */

	archive_set_error(&self->archive->archive, -1,
	    "External compression programs not supported on this platform");
	return (ARCHIVE_FATAL);
}