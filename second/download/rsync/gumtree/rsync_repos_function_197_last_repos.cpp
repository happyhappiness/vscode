char *get_backup_name(const char *fname)
{
	if (backup_dir) {
		static int initialized = 0;
		if (!initialized) {
			int ret;
			if (backup_dir_len > 1)
				backup_dir_buf[backup_dir_len-1] = '\0';
			ret = make_path(backup_dir_buf, 0);
			if (backup_dir_len > 1)
				backup_dir_buf[backup_dir_len-1] = '/';
			if (ret < 0)
				return NULL;
			initialized = 1;
		}
		/* copy fname into backup_dir_buf while validating the dirs. */
		if (copy_valid_path(fname))
			return backup_dir_buf;
		/* copy_valid_path() has printed an error message. */
		return NULL;
	}

	if (stringjoin(backup_dir_buf, MAXPATHLEN, fname, backup_suffix, NULL) < MAXPATHLEN)
		return backup_dir_buf;

	rprintf(FERROR, "backup filename too long\n");
	return NULL;
}