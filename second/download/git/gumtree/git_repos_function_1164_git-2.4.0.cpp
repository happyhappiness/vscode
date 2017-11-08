static char *vsnpath(char *buf, size_t n, const char *fmt, va_list args)
{
	const char *git_dir = get_git_dir();
	size_t len;

	len = strlen(git_dir);
	if (n < len + 1)
		goto bad;
	memcpy(buf, git_dir, len);
	if (len && !is_dir_sep(git_dir[len-1]))
		buf[len++] = '/';
	len += vsnprintf(buf + len, n - len, fmt, args);
	if (len >= n)
		goto bad;
	return cleanup_path(buf);
bad:
	strlcpy(buf, bad_path, n);
	return buf;
}