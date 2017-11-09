int make_path(char *fname, int flags)
{
	char *end, *p;
	int ret = 0;

	if (flags & MKP_SKIP_SLASH) {
		while (*fname == '/')
			fname++;
	}

	while (*fname == '.' && fname[1] == '/')
		fname += 2;

	if (flags & MKP_DROP_NAME) {
		end = strrchr(fname, '/');
		if (!end || end == fname)
			return 0;
		*end = '\0';
	} else
		end = fname + strlen(fname);

	/* Try to find an existing dir, starting from the deepest dir. */
	for (p = end; ; ) {
		if (dry_run) {
			STRUCT_STAT st;
			if (do_stat(fname, &st) == 0) {
				if (S_ISDIR(st.st_mode))
					errno = EEXIST;
				else
					errno = ENOTDIR;
			}
		} else if (do_mkdir(fname, ACCESSPERMS) == 0) {
			ret++;
			break;
		}

		if (errno != ENOENT) {
			STRUCT_STAT st;
			if (errno != EEXIST || (do_stat(fname, &st) == 0 && !S_ISDIR(st.st_mode)))
				ret = -ret - 1;
			break;
		}
		while (1) {
			if (p == fname) {
				/* We got a relative path that doesn't exist, so assume that '.'
				 * is there and just break out and create the whole thing. */
				p = NULL;
				goto double_break;
			}
			if (*--p == '/') {
				if (p == fname) {
					/* We reached the "/" dir, which we assume is there. */
					goto double_break;
				}
				*p = '\0';
				break;
			}
		}
	}
  double_break:

	/* Make all the dirs that we didn't find on the way here. */
	while (p != end) {
		if (p)
			*p = '/';
		else
			p = fname;
		p += strlen(p);
		if (ret < 0) /* Skip mkdir on error, but keep restoring the path. */
			continue;
		if (do_mkdir(fname, ACCESSPERMS) < 0)
			ret = -ret - 1;
		else
			ret++;
	}

	if (flags & MKP_DROP_NAME)
		*end = '/';

	return ret;
}