int sys_acl_valid( SMB_ACL_T theacl )
{
	acl_entry_t	entry;

	return acl_valid(theacl, &entry);
}