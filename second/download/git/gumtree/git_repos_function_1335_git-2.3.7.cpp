int odb_mkstemp(char *template, size_t limit, const char *pattern)
{
	int fd;
	/*
	 * we let the umask do its job, don't try to be more
	 * restrictive except to remove write permission.
	 */
	int mode = 0444;
	snprintf(template, limit, "%s/%s",
		 get_object_directory(), pattern);
	fd = git_mkstemp_mode(template, mode);
	if (0 <= fd)
		return fd;

	/* slow path */
	/* some mkstemp implementations erase template on failure */
	snprintf(template, limit, "%s/%s",
		 get_object_directory(), pattern);
	safe_create_leading_directories(template);
	return xmkstemp_mode(template, mode);
}