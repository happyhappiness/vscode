int sys_acl_free_acl(SMB_ACL_T acl_d) 
{
	SAFE_FREE(acl_d);
	return 0;
}