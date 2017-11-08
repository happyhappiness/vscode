void cache_xattr(struct file_struct *file, stat_x *sxp)
{
	int ndx;

	if (!sxp->xattr)
		return;

	ndx = find_matching_xattr(sxp->xattr);
	if (ndx < 0)
		rsync_xal_store(sxp->xattr); /* adds item to rsync_xal_l */

	F_XATTR(file) = ndx;
}