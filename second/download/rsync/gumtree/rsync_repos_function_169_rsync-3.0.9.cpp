int make_bak_dir(const char *fullpath)
{
	char fbuf[MAXPATHLEN], *rel, *end, *p;
	struct file_struct *file;
	int len = backup_dir_len;
	stat_x sx;

	while (*fullpath == '.' && fullpath[1] == '/') {
		fullpath += 2;
		len -= 2;
	}

	if (strlcpy(fbuf, fullpath, sizeof fbuf) >= sizeof fbuf)
		return -1;

	rel = fbuf + len;
	end = p = rel + strlen(rel);

	/* Try to find an existing dir, starting from the deepest dir. */
	while (1) {
		if (--p == fbuf)
			return -1;
		if (*p == '/') {
			*p = '\0';
			if (mkdir_defmode(fbuf) == 0)
				break;
			if (errno != ENOENT) {
				rsyserr(FERROR, errno,
					"make_bak_dir mkdir %s failed",
					full_fname(fbuf));
				return -1;
			}
		}
	}

	/* Make all the dirs that we didn't find on the way here. */
	while (1) {
		if (p >= rel) {
			/* Try to transfer the directory settings of the
			 * actual dir that the files are coming from. */
			if (x_stat(rel, &sx.st, NULL) < 0) {
				rsyserr(FERROR, errno,
					"make_bak_dir stat %s failed",
					full_fname(rel));
			} else {
#ifdef SUPPORT_ACLS
				sx.acc_acl = sx.def_acl = NULL;
#endif
#ifdef SUPPORT_XATTRS
				sx.xattr = NULL;
#endif
				if (!(file = make_file(rel, NULL, NULL, 0, NO_FILTERS)))
					continue;
#ifdef SUPPORT_ACLS
				if (preserve_acls && !S_ISLNK(file->mode)) {
					get_acl(rel, &sx);
					cache_tmp_acl(file, &sx);
					free_acl(&sx);
				}
#endif
#ifdef SUPPORT_XATTRS
				if (preserve_xattrs) {
					get_xattr(rel, &sx);
					cache_tmp_xattr(file, &sx);
					free_xattr(&sx);
				}
#endif
				set_file_attrs(fbuf, file, NULL, NULL, 0);
				unmake_file(file);
#ifdef SUPPORT_ACLS
				uncache_tmp_acls();
#endif
#ifdef SUPPORT_XATTRS
				uncache_tmp_xattrs();
#endif
			}
		}
		*p = '/';
		p += strlen(p);
		if (p == end)
			break;
		if (mkdir_defmode(fbuf) < 0) {
			rsyserr(FERROR, errno, "make_bak_dir mkdir %s failed",
				full_fname(fbuf));
			return -1;
		}
	}

	return 0;
}