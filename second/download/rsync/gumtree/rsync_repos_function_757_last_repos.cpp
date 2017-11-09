int sys_acl_get_entry( SMB_ACL_T the_acl, int entry_id, SMB_ACL_ENTRY_T *entry_p)
{
	SMB_ACL_ENTRY_T	entry;

	if (entry_id == SMB_ACL_FIRST_ENTRY && acl_first_entry(the_acl) != 0) {
		return -1;
	}

	errno = 0;
	if ((entry = acl_get_entry(the_acl)) != NULL) {
		*entry_p = entry;
		return 1;
	}

	return errno ? -1 : 0;
}