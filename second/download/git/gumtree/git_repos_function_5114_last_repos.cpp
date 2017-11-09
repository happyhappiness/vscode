static const char *add_prefix(const char *prefix, const char *path)
{
	return prefix_path(prefix, prefix ? strlen(prefix) : 0, path);
}