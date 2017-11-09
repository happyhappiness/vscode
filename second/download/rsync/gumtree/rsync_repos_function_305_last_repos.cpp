void itemize(const char *fnamecmp, struct file_struct *file, int ndx, int statret,
	     stat_x *sxp, int32 iflags, uchar fnamecmp_type,
	     const char *xname)
{
	if (statret >= 0) { /* A from-dest-dir statret can == 1! */
		int keep_time = !preserve_times ? 0
		    : S_ISDIR(file->mode) ? preserve_times & PRESERVE_DIR_TIMES
		    : S_ISLNK(file->mode) ? preserve_times & PRESERVE_LINK_TIMES
		    : 1;

		if (S_ISREG(file->mode) && F_LENGTH(file) != sxp->st.st_size)
			iflags |= ITEM_REPORT_SIZE;
		if (file->flags & FLAG_TIME_FAILED) { /* symlinks only */
			if (iflags & ITEM_LOCAL_CHANGE)
				iflags |= symlink_timeset_failed_flags;
		} else if (keep_time
		 ? cmp_time(file->modtime, sxp->st.st_mtime) != 0
		 : iflags & (ITEM_TRANSFER|ITEM_LOCAL_CHANGE) && !(iflags & ITEM_MATCHED)
		  && (!(iflags & ITEM_XNAME_FOLLOWS) || *xname))
			iflags |= ITEM_REPORT_TIME;
#if !defined HAVE_LCHMOD && !defined HAVE_SETATTRLIST
		if (S_ISLNK(file->mode)) {
			;
		} else
#endif
		if (preserve_perms) {
			if (!BITS_EQUAL(sxp->st.st_mode, file->mode, CHMOD_BITS))
				iflags |= ITEM_REPORT_PERMS;
		} else if (preserve_executability
		 && ((sxp->st.st_mode & 0111 ? 1 : 0) ^ (file->mode & 0111 ? 1 : 0)))
			iflags |= ITEM_REPORT_PERMS;
		if (uid_ndx && am_root && (uid_t)F_OWNER(file) != sxp->st.st_uid)
			iflags |= ITEM_REPORT_OWNER;
		if (gid_ndx && !(file->flags & FLAG_SKIP_GROUP)
		    && sxp->st.st_gid != (gid_t)F_GROUP(file))
			iflags |= ITEM_REPORT_GROUP;
#ifdef SUPPORT_ACLS
		if (preserve_acls && !S_ISLNK(file->mode)) {
			if (!ACL_READY(*sxp))
				get_acl(fnamecmp, sxp);
			if (set_acl(NULL, file, sxp, file->mode))
				iflags |= ITEM_REPORT_ACL;
		}
#endif
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs) {
			if (!XATTR_READY(*sxp))
				get_xattr(fnamecmp, sxp);
			if (xattr_diff(file, sxp, 1))
				iflags |= ITEM_REPORT_XATTR;
		}
#endif
	} else {
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs && xattr_diff(file, NULL, 1))
			iflags |= ITEM_REPORT_XATTR;
#endif
		iflags |= ITEM_IS_NEW;
	}

	iflags &= 0xffff;
	if ((iflags & (SIGNIFICANT_ITEM_FLAGS|ITEM_REPORT_XATTR) || INFO_GTE(NAME, 2)
	  || stdout_format_has_i > 1 || (xname && *xname)) && !read_batch) {
		if (protocol_version >= 29) {
			if (ndx >= 0)
				write_ndx(sock_f_out, ndx);
			write_shortint(sock_f_out, iflags);
			if (iflags & ITEM_BASIS_TYPE_FOLLOWS)
				write_byte(sock_f_out, fnamecmp_type);
			if (iflags & ITEM_XNAME_FOLLOWS)
				write_vstring(sock_f_out, xname, strlen(xname));
#ifdef SUPPORT_XATTRS
			if (preserve_xattrs && do_xfers
			 && iflags & (ITEM_REPORT_XATTR|ITEM_TRANSFER)) {
				int fd = iflags & ITEM_REPORT_XATTR
				      && !(want_xattr_optim && BITS_SET(iflags, ITEM_XNAME_FOLLOWS|ITEM_LOCAL_CHANGE))
				       ? sock_f_out : -1;
				send_xattr_request(NULL, file, fd);
			}
#endif
		} else if (ndx >= 0) {
			enum logcode code = logfile_format_has_i ? FINFO : FCLIENT;
			log_item(code, file, iflags, xname);
		}
	}
}