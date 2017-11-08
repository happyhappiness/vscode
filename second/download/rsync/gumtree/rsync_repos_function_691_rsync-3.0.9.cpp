int sys_acl_get_entry( SMB_ACL_T the_acl, int entry_id, SMB_ACL_ENTRY_T *entry_p)
{
	return acl_get_entry( the_acl, entry_id, entry_p);
}