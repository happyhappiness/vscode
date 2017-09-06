int
archive_read_support_filter_program_signature(struct archive *_a,
    const char *cmd, const void *signature, size_t signature_len)
{
	(void)_a; /* UNUSED */
	(void)cmd; /* UNUSED */
	(void)signature; /* UNUSED */
	(void)signature_len; /* UNUSED */

	archive_set_error(_a, -1,
	    "External compression programs not supported on this platform");
	return (ARCHIVE_FATAL);
}