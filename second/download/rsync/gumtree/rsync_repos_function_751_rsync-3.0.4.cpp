int sys_acl_valid(SMB_ACL_T theacl)
{
	return acl_valid(theacl);
}