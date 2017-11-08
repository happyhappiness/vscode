int set_xattr(const char *fname, const struct file_struct *file,
	      const char *fnamecmp, stat_x *sxp)
{
	int ndx;
	item_list *lst = rsync_xal_l.items;

	if (dry_run)
		return 1; /* FIXME: --dry-run needs to compute this value */

	if (read_only || list_only) {
		errno = EROFS;
		return -1;
	}

	ndx = F_XATTR(file);
	return rsync_xal_set(fname, lst + ndx, fnamecmp, sxp);
}