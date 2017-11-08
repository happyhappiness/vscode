char *get_backup_name(const char *fname)
{
	if (backup_dir) {
		if (stringjoin(backup_dir_buf + backup_dir_len, backup_dir_remainder,
			       fname, backup_suffix, NULL) < backup_dir_remainder)
			return backup_dir_buf;
	} else {
		if (stringjoin(backup_dir_buf, MAXPATHLEN,
			       fname, backup_suffix, NULL) < MAXPATHLEN)
			return backup_dir_buf;
	}

	rprintf(FERROR, "backup filename too long\n");
	return NULL;
}