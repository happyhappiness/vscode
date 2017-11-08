void cache_acl(struct file_struct *file, stat_x *sxp)
{
	F_ACL(file) = cache_rsync_acl(sxp->acc_acl,
				      SMB_ACL_TYPE_ACCESS, &access_acl_list);

	if (S_ISDIR(sxp->st.st_mode)) {
		F_DIR_DEFACL(file) = cache_rsync_acl(sxp->def_acl,
				      SMB_ACL_TYPE_DEFAULT, &default_acl_list);
	}
}