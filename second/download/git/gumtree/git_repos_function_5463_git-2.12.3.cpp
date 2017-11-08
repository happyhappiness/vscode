static char *prefix_copy(const char *prefix, const char *filename)
{
	if (!prefix || is_absolute_path(filename))
		return xstrdup(filename);
	return xstrdup(prefix_filename(prefix, strlen(prefix), filename));
}