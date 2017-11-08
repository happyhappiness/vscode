static inline int acls_differ(const char *fname, struct file_struct *file, stat_x *sxp)
{
	if (preserve_acls) {
		if (!ACL_READY(*sxp))
			get_acl(fname, sxp);
		if (set_acl(NULL, file, sxp, file->mode))
			return 1;
	}

	return 0;
}