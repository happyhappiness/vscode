 * is set) if the path is absolute.
 */
static int
cleanup_pathname(struct archive_write_disk *a)
{
	char *dest, *src;
	char separator = '\0';

	dest = src = a->name;
	if (*src == '\0') {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid empty pathname");
		return (ARCHIVE_FAILED);
	}

#if defined(__CYGWIN__)
	cleanup_pathname_win(a);
#endif
	/* Skip leading '/'. */
	if (*src == '/') {
		if (a->flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			                  "Path is absolute");
			return (ARCHIVE_FAILED);
		}

