static inline int perms_differ(struct file_struct *file, stat_x *sxp)
{
	if (preserve_perms)
		return !BITS_EQUAL(sxp->st.st_mode, file->mode, CHMOD_BITS);

	if (preserve_executability)
		return (sxp->st.st_mode & 0111 ? 1 : 0) ^ (file->mode & 0111 ? 1 : 0);

	return 0;
}