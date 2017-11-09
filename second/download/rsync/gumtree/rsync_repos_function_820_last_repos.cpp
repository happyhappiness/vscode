int sys_acl_set_access_bits(SMB_ACL_ENTRY_T entry, uint32 bits)
{
	DEBUG(10,("Starting AIX sys_acl_set_permset\n"));
	entry->ace_access = bits;
	DEBUG(10,("entry->ace_access = %d\n",entry->ace_access));
	DEBUG(10,("Ending AIX sys_acl_set_permset\n"));
	return(0);
}