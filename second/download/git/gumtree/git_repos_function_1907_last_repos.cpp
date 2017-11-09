int odb_mkstemp(struct strbuf *template, const char *pattern)
{
	int fd;
	/*
	 * we let the umask do its job, don't try to be more
	 * restrictive except to remove write permission.
	 */
	int mode = 0444;
	git_path_buf(template, "objects/%s", pattern);
	fd = git_mkstemp_mode(template->buf, mode);
	if (0 <= fd)
		return fd;

	/* slow path */
	/* some mkstemp implementations erase template on failure */
	git_path_buf(template, "objects/%s", pattern);
	safe_create_leading_directories(template->buf);
	return xmkstemp_mode(template->buf, mode);
}