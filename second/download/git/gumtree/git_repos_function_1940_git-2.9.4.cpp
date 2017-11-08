char *prefix_path(const char *prefix, int len, const char *path)
{
	char *r = prefix_path_gently(prefix, len, NULL, path);
	if (!r)
		die("'%s' is outside repository", path);
	return r;
}