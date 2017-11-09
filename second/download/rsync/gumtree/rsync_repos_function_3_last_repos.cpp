uint16 get_del_for_flag(uint16 mode)
{
	if (S_ISREG(mode))
		return DEL_FOR_FILE;
	if (S_ISDIR(mode))
		return DEL_FOR_DIR;
	if (S_ISLNK(mode))
		return DEL_FOR_SYMLINK;
	if (IS_DEVICE(mode))
		return DEL_FOR_DEVICE;
	if (IS_SPECIAL(mode))
		return DEL_FOR_SPECIAL;
	exit_cleanup(RERR_UNSUPPORTED); /* IMPOSSIBLE */
}