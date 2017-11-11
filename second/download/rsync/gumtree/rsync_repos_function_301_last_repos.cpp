static inline int ownership_differs(struct file_struct *file, stat_x *sxp)
{
	if (am_root && uid_ndx && sxp->st.st_uid != (uid_t)F_OWNER(file))
		return 1;

	if (gid_ndx && !(file->flags & FLAG_SKIP_GROUP) && sxp->st.st_gid != (gid_t)F_GROUP(file))
		return 1;

	return 0;
}