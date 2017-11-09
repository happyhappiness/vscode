void set_filter_dir(const char *dir, unsigned int dirlen)
{
	unsigned int len;
	if (*dir != '/') {
		memcpy(dirbuf, curr_dir, curr_dir_len);
		dirbuf[curr_dir_len] = '/';
		len = curr_dir_len + 1;
		if (len + dirlen >= MAXPATHLEN)
			dirlen = 0;
	} else
		len = 0;
	memcpy(dirbuf + len, dir, dirlen);
	dirbuf[dirlen + len] = '\0';
	dirbuf_len = clean_fname(dirbuf, CFN_COLLAPSE_DOT_DOT_DIRS);
	if (dirbuf_len > 1 && dirbuf[dirbuf_len-1] == '.'
	    && dirbuf[dirbuf_len-2] == '/')
		dirbuf_len -= 2;
	if (dirbuf_len != 1)
		dirbuf[dirbuf_len++] = '/';
	dirbuf[dirbuf_len] = '\0';
	if (sanitize_paths)
		dirbuf_depth = count_dir_elements(dirbuf + module_dirlen);
}