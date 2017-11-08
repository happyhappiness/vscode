int readlink_stat(const char *path, STRUCT_STAT * buffer, char *linkbuf)
{
#if SUPPORT_LINKS
	if (copy_links) {
		return do_stat(path, buffer);
	}
	if (do_lstat(path, buffer) == -1) {
		return -1;
	}
	if (S_ISLNK(buffer->st_mode)) {
		int l;
		l = readlink((char *) path, linkbuf, MAXPATHLEN - 1);
		if (l == -1)
			return -1;
		linkbuf[l] = 0;
		if (copy_unsafe_links && unsafe_symlink(linkbuf, path)) {
			if (verbose > 1) {
				rprintf(FINFO,"copying unsafe symlink \"%s\" -> \"%s\"\n",
					path, linkbuf);
			}
			return do_stat(path, buffer);
		}
	}
	return 0;
#else
	return do_stat(path, buffer);
#endif
}