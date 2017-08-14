static int
set_timefilter_pathname_mbs(struct archive_match *a, int timetype,
    const char *path)
{
	struct stat st;

	if (path == NULL || *path == '\0') {
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}
	if (stat(path, &st) != 0) {
		archive_set_error(&(a->archive), errno, "Failed to stat()");
		return (ARCHIVE_FAILED);
	}
	return (set_timefilter_stat(a, timetype, &st));
}