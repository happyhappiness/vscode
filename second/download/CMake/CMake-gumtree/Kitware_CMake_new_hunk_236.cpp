 * is set) if the path is absolute.
 */
static int
cleanup_pathname_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
    int flags)
{
	char *dest, *src;
	char separator = '\0';

	dest = src = path;
	if (*src == '\0') {
		fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
		    "Invalid empty ", "pathname");
		return (ARCHIVE_FAILED);
	}

#if defined(__CYGWIN__)
	cleanup_pathname_win(path);
#endif
	/* Skip leading '/'. */
	if (*src == '/') {
		if (flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
			fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
			    "Path is ", "absolute");
			return (ARCHIVE_FAILED);
		}

