int get_acl(const char *fname, stat_x *sxp)
{
	sxp->acc_acl = create_racl();

	if (S_ISREG(sxp->st.st_mode) || S_ISDIR(sxp->st.st_mode)) {
		/* Everyone supports this. */
	} else if (S_ISLNK(sxp->st.st_mode)) {
		return 0;
	} else if (IS_SPECIAL(sxp->st.st_mode)) {
#ifndef NO_SPECIAL_ACLS
		if (!preserve_specials)
#endif
			return 0;
	} else if (IS_DEVICE(sxp->st.st_mode)) {
#ifndef NO_DEVICE_ACLS
		if (!preserve_devices)
#endif
			return 0;
	} else if (IS_MISSING_FILE(sxp->st))
		return 0;

	if (get_rsync_acl(fname, sxp->acc_acl, SMB_ACL_TYPE_ACCESS,
			  sxp->st.st_mode) < 0) {
		free_acl(sxp);
		return -1;
	}

	if (S_ISDIR(sxp->st.st_mode)) {
		sxp->def_acl = create_racl();
		if (get_rsync_acl(fname, sxp->def_acl, SMB_ACL_TYPE_DEFAULT,
				  sxp->st.st_mode) < 0) {
			free_acl(sxp);
			return -1;
		}
	}

	return 0;
}