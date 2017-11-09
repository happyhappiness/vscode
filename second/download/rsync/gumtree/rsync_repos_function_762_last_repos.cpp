int sys_acl_create_entry( SMB_ACL_T *pacl, SMB_ACL_ENTRY_T *pentry)
{
	SMB_ACL_ENTRY_T entry;

	if ((entry = acl_create_entry(pacl)) == NULL) {
		return -1;
	}

	*pentry = entry;
	return 0;
}