static inline mode_t mode_native_to_git(mode_t native_mode)
{
	mode_t perm_bits = native_mode & 07777;
	if (S_ISREG(native_mode))
		return 0100000 | perm_bits;
	if (S_ISDIR(native_mode))
		return 0040000 | perm_bits;
	if (S_ISLNK(native_mode))
		return 0120000 | perm_bits;
	if (S_ISBLK(native_mode))
		return 0060000 | perm_bits;
	if (S_ISCHR(native_mode))
		return 0020000 | perm_bits;
	if (S_ISFIFO(native_mode))
		return 0010000 | perm_bits;
	if (S_ISSOCK(native_mode))
		return 0140000 | perm_bits;
	/* Non-standard type bits were given. */
	return perm_bits;
}