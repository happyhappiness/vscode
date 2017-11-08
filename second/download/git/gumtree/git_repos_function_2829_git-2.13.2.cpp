char *prefix_filename(const char *pfx, const char *arg)
{
	struct strbuf path = STRBUF_INIT;
	size_t pfx_len = pfx ? strlen(pfx) : 0;

	if (!pfx_len)
		; /* nothing to prefix */
	else if (is_absolute_path(arg))
		pfx_len = 0;
	else
		strbuf_add(&path, pfx, pfx_len);

	strbuf_addstr(&path, arg);
#ifdef GIT_WINDOWS_NATIVE
	convert_slashes(path.buf + pfx_len);
#endif
	return strbuf_detach(&path, NULL);
}