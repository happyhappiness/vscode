char *alloc_sanitize_path(const char *path, const char *rootdir)
{
	char *buf;
	int rlen, plen = strlen(path);

	if (*path == '/' && rootdir) {
		rlen = strlen(rootdir);
		if (rlen == 1)
			path++;
	} else
		rlen = 0;
	if (!(buf = new_array(char, rlen + plen + 1)))
		out_of_memory("alloc_sanitize_path");
	if (rlen)
		memcpy(buf, rootdir, rlen);
	memcpy(buf + rlen, path, plen + 1);

	if (rlen > 1)
		rlen++;
	sanitize_path(buf + rlen, NULL);
	if (rlen && buf[rlen] == '.' && buf[rlen+1] == '\0') {
		if (rlen > 1)
			rlen--;
		buf[rlen] = '\0';
	}

	return buf;
}