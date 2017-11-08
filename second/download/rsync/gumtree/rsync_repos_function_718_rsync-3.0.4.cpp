int sys_acl_valid(SMB_ACL_T acl_d)
{
	return acl_sort(acl_d);
}