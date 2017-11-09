int sys_acl_get_entry(SMB_ACL_T acl_d, int entry_id, SMB_ACL_ENTRY_T *entry_p)
{
	if (entry_id != SMB_ACL_FIRST_ENTRY && entry_id != SMB_ACL_NEXT_ENTRY) {
		errno = EINVAL;
		return -1;
	}

	if (entry_p == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (entry_id == SMB_ACL_FIRST_ENTRY) {
		acl_d->next = 0;
	}

	if (acl_d->next < 0) {
		errno = EINVAL;
		return -1;
	}

	if (acl_d->next >= acl_d->count) {
		return 0;
	}

	*entry_p = &acl_d->acl[acl_d->next++];

	return 1;
}