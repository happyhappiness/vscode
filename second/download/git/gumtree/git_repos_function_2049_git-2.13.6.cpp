enum scld_error safe_create_leading_directories_const(const char *path)
{
	int save_errno;
	/* path points to cache entries, so xstrdup before messing with it */
	char *buf = xstrdup(path);
	enum scld_error result = safe_create_leading_directories(buf);

	save_errno = errno;
	free(buf);
	errno = save_errno;
	return result;
}