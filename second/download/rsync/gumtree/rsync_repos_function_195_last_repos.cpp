static int validate_backup_dir(void)
{
	STRUCT_STAT st;

	if (do_lstat(backup_dir_buf, &st) < 0) {
		if (errno == ENOENT)
			return 0;
		rsyserr(FERROR, errno, "backup lstat %s failed", backup_dir_buf);
		return -1;
	}
	if (!S_ISDIR(st.st_mode)) {
		int flags = get_del_for_flag(st.st_mode) | DEL_FOR_BACKUP | DEL_RECURSE;
		if (delete_item(backup_dir_buf, st.st_mode, flags) == 0)
			return 0;
		return -1;
	}
	return 1;
}