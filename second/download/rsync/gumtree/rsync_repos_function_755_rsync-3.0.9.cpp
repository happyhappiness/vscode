int sys_acl_valid(SMB_ACL_T acl_d)
{
	return acl_valid(acl_d->aclp);
}