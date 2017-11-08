int set_acl(const char *fname, const struct file_struct *file, stat_x *sxp)
{
	int unchanged = 1;
	int32 ndx;
	BOOL eq;

	if (!dry_run && (read_only || list_only)) {
		errno = EROFS;
		return -1;
	}

	ndx = F_ACL(file);
	if (ndx >= 0 && (size_t)ndx < access_acl_list.count) {
		acl_duo *duo_item = access_acl_list.items;
		duo_item += ndx;
		eq = sxp->acc_acl
		  && rsync_acl_equal_enough(sxp->acc_acl, &duo_item->racl, file->mode);
		if (!eq) {
			unchanged = 0;
			if (!dry_run && fname
			 && set_rsync_acl(fname, duo_item, SMB_ACL_TYPE_ACCESS,
					  sxp, file->mode) < 0)
				unchanged = -1;
		}
	}

	if (!S_ISDIR(sxp->st.st_mode))
		return unchanged;

	ndx = F_DIR_DEFACL(file);
	if (ndx >= 0 && (size_t)ndx < default_acl_list.count) {
		acl_duo *duo_item = default_acl_list.items;
		duo_item += ndx;
		eq = sxp->def_acl && rsync_acl_equal(sxp->def_acl, &duo_item->racl);
		if (!eq) {
			if (unchanged > 0)
				unchanged = 0;
			if (!dry_run && fname
			 && set_rsync_acl(fname, duo_item, SMB_ACL_TYPE_DEFAULT,
					  sxp, file->mode) < 0)
				unchanged = -1;
		}
	}

	return unchanged;
}