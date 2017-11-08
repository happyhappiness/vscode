int get_acl(const char *fname, stat_x *sxp)
{
	sxp->acc_acl = create_racl();
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