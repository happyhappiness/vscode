int git_mkstemps(char *path, size_t len, const char *template, int suffix_len)
{
	const char *tmp;
	size_t n;

	tmp = getenv("TMPDIR");
	if (!tmp)
		tmp = "/tmp";
	n = snprintf(path, len, "%s/%s", tmp, template);
	if (len <= n) {
		errno = ENAMETOOLONG;
		return -1;
	}
	return mkstemps(path, suffix_len);
}