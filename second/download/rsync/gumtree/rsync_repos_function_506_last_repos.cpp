static int set_rsync_acl(const char *fname, acl_duo *duo_item,
			 SMB_ACL_TYPE_T type, stat_x *sxp, mode_t mode)
{
	if (type == SMB_ACL_TYPE_DEFAULT
	 && duo_item->racl.user_obj == NO_ENTRY) {
		int rc;
#ifdef SUPPORT_XATTRS
		/* --fake-super support: delete default ACL from xattrs. */
		if (am_root < 0)
			rc = del_def_xattr_acl(fname);
		else
#endif
			rc = sys_acl_delete_def_file(fname);
		if (rc < 0) {
			rsyserr(FERROR_XFER, errno, "set_acl: sys_acl_delete_def_file(%s)",
				fname);
			return -1;
		}
#ifdef SUPPORT_XATTRS
	} else if (am_root < 0) {
		/* --fake-super support: store ACLs in an xattr. */
		int cnt = duo_item->racl.names.count;
		size_t len = 4*4 + cnt * (4+4);
		char *buf = new_array(char, len);
		int rc;

		SIVAL(buf, 0, duo_item->racl.user_obj);
		SIVAL(buf, 4, duo_item->racl.group_obj);
		SIVAL(buf, 8, duo_item->racl.mask_obj);
		SIVAL(buf, 12, duo_item->racl.other_obj);

		if (cnt) {
			char *bp = buf + 4*4;
			id_access *ida = duo_item->racl.names.idas;
			for ( ; cnt--; ida++, bp += 4+4) {
				SIVAL(bp, 0, ida->id);
				SIVAL(bp, 4, ida->access);
			}
		}
		rc = set_xattr_acl(fname, type == SMB_ACL_TYPE_ACCESS, buf, len);
		free(buf);
		return rc;
#endif
	} else {
		mode_t cur_mode = sxp->st.st_mode;
		if (!duo_item->sacl
		 && !pack_smb_acl(&duo_item->sacl, &duo_item->racl))
			return -1;
#ifdef HAVE_OSX_ACLS
		mode = 0; /* eliminate compiler warning */
#else
		if (type == SMB_ACL_TYPE_ACCESS) {
			cur_mode = change_sacl_perms(duo_item->sacl, &duo_item->racl,
						     cur_mode, mode);
			if (cur_mode == (mode_t)-1)
				return 0;
		}
#endif
		if (sys_acl_set_file(fname, type, duo_item->sacl) < 0) {
			rsyserr(FERROR_XFER, errno, "set_acl: sys_acl_set_file(%s, %s)",
				fname, str_acl_type(type));
			return -1;
		}
		if (type == SMB_ACL_TYPE_ACCESS)
			sxp->st.st_mode = cur_mode;
	}

	return 0;
}