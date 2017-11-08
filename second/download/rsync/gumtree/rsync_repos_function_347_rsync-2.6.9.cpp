static int readlink_stat(const char *path, STRUCT_STAT *stp, char *linkbuf)
{
#ifdef SUPPORT_LINKS
	if (link_stat(path, stp, copy_dirlinks) < 0)
		return -1;
	if (S_ISLNK(stp->st_mode)) {
		int llen = readlink(path, linkbuf, MAXPATHLEN - 1);
		if (llen < 0)
			return -1;
		linkbuf[llen] = '\0';
		if (copy_unsafe_links && unsafe_symlink(linkbuf, path)) {
			if (verbose > 1) {
				rprintf(FINFO,"copying unsafe symlink \"%s\" -> \"%s\"\n",
					path, linkbuf);
			}
			return do_stat(path, stp);
		}
	}
	return 0;
#else
	return do_stat(path, stp);
#endif
}