int sys_acl_delete_def_file(const char *path)
{
	SMB_ACL_T	acl_d;
	int		ret;

	/*
	 * fetching the access ACL and rewriting it has
	 * the effect of deleting the default ACL
	 */
	if ((acl_d = sys_acl_get_file(path, SMB_ACL_TYPE_ACCESS)) == NULL) {
		return -1;
	}

	ret = acl(path, ACL_SET, acl_d->count, acl_d->acl);

	sys_acl_free_acl(acl_d);
	
	return ret;
}