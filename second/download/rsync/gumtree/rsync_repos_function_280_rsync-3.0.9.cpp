int unchanged_attrs(const char *fname, struct file_struct *file, stat_x *sxp)
{
	if (S_ISLNK(file->mode)) {
#ifdef CAN_SET_SYMLINK_TIMES
		if (preserve_times & PRESERVE_LINK_TIMES && time_differs(file, sxp))
			return 0;
#endif
#ifdef CAN_CHMOD_SYMLINK
		if (perms_differ(file, sxp))
			return 0;
#endif
#ifdef CAN_CHOWN_SYMLINK
		if (ownership_differs(file, sxp))
			return 0;
#endif
#if defined SUPPORT_ACLS && 0 /* no current symlink-ACL support */
		if (acls_differ(fname, file, sxp))
			return 0;
#endif
#if defined SUPPORT_XATTRS && !defined NO_SYMLINK_XATTRS
		if (xattrs_differ(fname, file, sxp))
			return 0;
#endif
	} else {
		if (preserve_times && time_differs(file, sxp))
			return 0;
		if (perms_differ(file, sxp))
			return 0;
		if (ownership_differs(file, sxp))
			return 0;
#ifdef SUPPORT_ACLS
		if (acls_differ(fname, file, sxp))
			return 0;
#endif
#ifdef SUPPORT_XATTRS
		if (xattrs_differ(fname, file, sxp))
			return 0;
#endif
	}

	return 1;
}