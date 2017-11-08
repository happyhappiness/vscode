int unchanged_attrs(const char *fname, struct file_struct *file, stat_x *sxp)
{
#if !defined HAVE_LUTIMES || !defined HAVE_UTIMES
	if (S_ISLNK(file->mode)) {
		;
	} else
#endif
	if (preserve_times && cmp_time(sxp->st.st_mtime, file->modtime) != 0)
		return 0;

	if (preserve_perms) {
		if (!BITS_EQUAL(sxp->st.st_mode, file->mode, CHMOD_BITS))
			return 0;
	} else if (preserve_executability
	 && ((sxp->st.st_mode & 0111 ? 1 : 0) ^ (file->mode & 0111 ? 1 : 0)))
		return 0;

	if (am_root && uid_ndx && sxp->st.st_uid != (uid_t)F_OWNER(file))
		return 0;

	if (gid_ndx && !(file->flags & FLAG_SKIP_GROUP) && sxp->st.st_gid != (gid_t)F_GROUP(file))
		return 0;

#ifdef SUPPORT_ACLS
	if (preserve_acls && !S_ISLNK(file->mode)) {
		if (!ACL_READY(*sxp))
			get_acl(fname, sxp);
		if (set_acl(NULL, file, sxp) == 0)
			return 0;
	}
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs) {
		if (!XATTR_READY(*sxp))
			get_xattr(fname, sxp);
		if (xattr_diff(file, sxp, 0))
			return 0;
	}
#endif

	return 1;
}