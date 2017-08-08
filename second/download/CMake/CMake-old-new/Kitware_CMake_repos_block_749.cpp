{
	(void)buff; /* UNUSED */
	(void)s; /* UNUSED */
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC, "Programing error");
	return (ARCHIVE_FATAL);
}