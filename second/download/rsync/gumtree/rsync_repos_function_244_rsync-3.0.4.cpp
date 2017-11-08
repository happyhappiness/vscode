int get_xattr(const char *fname, stat_x *sxp)
{
	sxp->xattr = new(item_list);
	*sxp->xattr = empty_xattr;
	if (rsync_xal_get(fname, sxp->xattr) < 0) {
		free_xattr(sxp);
		return -1;
	}
	return 0;
}