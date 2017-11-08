static int make_bak_dir(char *fullpath)
{
	STRUCT_STAT st;
	char *rel = fullpath + backup_dir_len;
	char *end = rel + strlen(rel);
	char *p = end;

	while (strncmp(fullpath, "./", 2) == 0)
		fullpath += 2;

	/* Try to find an existing dir, starting from the deepest dir. */
	while (1) {
		if (--p == fullpath) {
			p += strlen(p);
			goto failure;
		}
		if (*p == '/') {
			*p = '\0';
			if (do_mkdir(fullpath, 0777 & ~orig_umask) == 0)
				break;
			if (errno != ENOENT) {
				rprintf(FERROR,
				    "make_bak_dir mkdir %s failed: %s\n",
				    full_fname(fullpath), strerror(errno));
				goto failure;
			}
		}
	}

	/* Make all the dirs that we didn't find on the way here. */
	while (1) {
		if (p >= rel) {
			/* Try to transfer the directory settings of the
			 * actual dir that the files are coming from. */
			if (do_lstat(rel, &st) != 0) {
				rprintf(FERROR,
				    "make_bak_dir stat %s failed: %s\n",
				    full_fname(rel), strerror(errno));
			} else {
				set_modtime(fullpath, st.st_mtime);
				do_lchown(fullpath, st.st_uid, st.st_gid);
				do_chmod(fullpath, st.st_mode);
			}
		}
		*p = '/';
		p += strlen(p);
		if (p == end)
			break;
		if (do_mkdir(fullpath, 0777 & ~orig_umask) < 0) {
			rprintf(FERROR,
			    "make_bak_dir mkdir %s failed: %s\n",
			    full_fname(fullpath), strerror(errno));
			goto failure;
		}
	}
	return 0;

failure:
	while (p != end) {
		*p = '/';
		p += strlen(p);
	}
	return -1;
}