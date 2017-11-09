int set_acl(const char *fname, const struct file_struct *file, stat_x *sxp, mode_t new_mode)
{
	int changed = 0;
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
		  && rsync_acl_equal_enough(sxp->acc_acl, &duo_item->racl, new_mode);
		if (!eq) {
			changed = 1;
			if (!dry_run && fname
			 && set_rsync_acl(fname, duo_item, SMB_ACL_TYPE_ACCESS,
					  sxp, new_mode) < 0)
				return -1;
		}
	}

	if (!S_ISDIR(new_mode))
		return changed;

	ndx = F_DIR_DEFACL(file);
	if (ndx >= 0 && (size_t)ndx < default_acl_list.count) {
		acl_duo *duo_item = default_acl_list.items;
		duo_item += ndx;
		eq = sxp->def_acl && rsync_acl_equal(sxp->def_acl, &duo_item->racl);
		if (!eq) {
			changed = 1;
			if (!dry_run && fname
			 && set_rsync_acl(fname, duo_item, SMB_ACL_TYPE_DEFAULT,
					  sxp, new_mode) < 0)
				return -1;
		}
	}

	return changed;
}