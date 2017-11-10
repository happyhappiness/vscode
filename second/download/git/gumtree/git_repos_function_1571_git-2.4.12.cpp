enum scld_error safe_create_leading_directories_const(const char *path)
{
	/* path points to cache entries, so xstrdup before messing with it */
	char *buf = xstrdup(path);
	enum scld_error result = safe_create_leading_directories(buf);
	free(buf);
	return result;
}