static inline int time_differs(struct file_struct *file, stat_x *sxp)
{
	return cmp_time(sxp->st.st_mtime, file->modtime);
}