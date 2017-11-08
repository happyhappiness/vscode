const char *prefix_filename(const char *pfx, int pfx_len, const char *arg)
{
	static struct strbuf path = STRBUF_INIT;
#ifndef GIT_WINDOWS_NATIVE
	if (!pfx_len || is_absolute_path(arg))
		return arg;
	strbuf_reset(&path);
	strbuf_add(&path, pfx, pfx_len);
	strbuf_addstr(&path, arg);
#else
	char *p;
	/* don't add prefix to absolute paths, but still replace '\' by '/' */
	strbuf_reset(&path);
	if (is_absolute_path(arg))
		pfx_len = 0;
	else if (pfx_len)
		strbuf_add(&path, pfx, pfx_len);
	strbuf_addstr(&path, arg);
	for (p = path.buf + pfx_len; *p; p++)
		if (*p == '\\')
			*p = '/';
#endif
	return path.buf;
}