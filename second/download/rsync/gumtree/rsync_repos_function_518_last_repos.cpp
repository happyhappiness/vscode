static int readlink_stat(const char *path, STRUCT_STAT *stp, char *linkbuf)
{
#ifdef SUPPORT_LINKS
	if (link_stat(path, stp, copy_dirlinks) < 0)
		return -1;
	if (S_ISLNK(stp->st_mode)) {
		int llen = do_readlink(path, linkbuf, MAXPATHLEN - 1);
		if (llen < 0)
			return -1;
		linkbuf[llen] = '\0';
		if (copy_unsafe_links && unsafe_symlink(linkbuf, path)) {
			if (INFO_GTE(SYMSAFE, 1)) {
				rprintf(FINFO,"copying unsafe symlink \"%s\" -> \"%s\"\n",
					path, linkbuf);
			}
			return x_stat(path, stp, NULL);
		}
		if (munge_symlinks && am_sender && llen > SYMLINK_PREFIX_LEN
		 && strncmp(linkbuf, SYMLINK_PREFIX, SYMLINK_PREFIX_LEN) == 0) {
			memmove(linkbuf, linkbuf + SYMLINK_PREFIX_LEN,
				llen - SYMLINK_PREFIX_LEN + 1);
		}
	}
	return 0;
#else
	return x_stat(path, stp, NULL);
#endif
}