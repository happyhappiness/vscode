static inline int xattrs_differ(const char *fname, struct file_struct *file, stat_x *sxp)
{
	if (preserve_xattrs) {
		if (!XATTR_READY(*sxp))
			get_xattr(fname, sxp);
		if (xattr_diff(file, sxp, 0))
			return 1;
	}

	return 0;
}