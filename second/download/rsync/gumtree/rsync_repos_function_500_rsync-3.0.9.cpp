int change_pathname(struct file_struct *file, const char *dir, int dirlen)
{
	if (dirlen < 0) {
		char *cpy = strdup(dir);
		if (*cpy != '/')
			change_dir(orig_dir, CD_SKIP_CHDIR);
		if (path_is_daemon_excluded(cpy, 0))
			goto chdir_error;
		dir = cpy;
		dirlen = -dirlen;
	} else {
		if (file) {
			if (pathname == F_PATHNAME(file))
				return 1;
			dir = F_PATHNAME(file);
			if (dir)
				dirlen = strlen(dir);
		} else if (pathname == dir)
			return 1;
		if (dir && *dir != '/')
			change_dir(orig_dir, CD_SKIP_CHDIR);
	}

	pathname = dir;
	pathname_len = dirlen;

	if (!dir)
		dir = orig_dir;

	if (!change_dir(dir, CD_NORMAL)) {
	  chdir_error:
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR_XFER, errno, "change_dir %s failed", full_fname(dir));
		if (dir != orig_dir)
			change_dir(orig_dir, CD_NORMAL);
		pathname = NULL;
		pathname_len = 0;
		return 0;
	}

	return 1;
}