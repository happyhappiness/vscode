static const char *add_slash(const char *path)
{
	int len = strlen(path);
	if (path[len - 1] != '/') {
		char *with_slash = xmalloc(len + 2);
		memcpy(with_slash, path, len);
		with_slash[len++] = '/';
		with_slash[len] = 0;
		return with_slash;
	}
	return path;
}