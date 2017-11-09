int sys_acl_create_entry(SMB_ACL_T *acl_p, SMB_ACL_ENTRY_T *entry_p)
{
	SMB_ACL_T	acl_d;
	SMB_ACL_ENTRY_T	entry_d;

	if (acl_p == NULL || entry_p == NULL || (acl_d = *acl_p) == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (acl_d->aclp->acl_cnt >= ACL_MAX_ENTRIES) {
		errno = ENOSPC;
		return -1;
	}

	entry_d		= &acl_d->aclp->acl_entry[acl_d->aclp->acl_cnt++];
	entry_d->ae_tag	= 0;
	entry_d->ae_id	= 0;
	entry_d->ae_perm	= 0;
	*entry_p	= entry_d;

	return 0;
}