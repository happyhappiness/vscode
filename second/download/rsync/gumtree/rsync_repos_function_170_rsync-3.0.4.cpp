static int robust_move(const char *src, char *dst)
{
	if (robust_rename(src, dst, NULL, 0755) < 0) {
		int save_errno = errno ? errno : EINVAL; /* 0 paranoia */
		if (errno == ENOENT && make_bak_dir(dst) == 0) {
			if (robust_rename(src, dst, NULL, 0755) < 0)
				save_errno = errno ? errno : save_errno;
			else
				save_errno = 0;
		}
		if (save_errno) {
			errno = save_errno;
			return -1;
		}
	}
	return 0;
}