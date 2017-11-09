void cache_tmp_acl(struct file_struct *file, stat_x *sxp)
{
	if (prior_access_count == (size_t)-1)
		prior_access_count = access_acl_list.count;

	F_ACL(file) = cache_rsync_acl(sxp->acc_acl,
				      SMB_ACL_TYPE_ACCESS, &access_acl_list);

	if (S_ISDIR(sxp->st.st_mode)) {
		if (prior_default_count == (size_t)-1)
			prior_default_count = default_acl_list.count;
		F_DIR_DEFACL(file) = cache_rsync_acl(sxp->def_acl,
				      SMB_ACL_TYPE_DEFAULT, &default_acl_list);
	}
}