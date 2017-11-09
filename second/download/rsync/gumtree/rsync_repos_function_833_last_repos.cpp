int sys_acl_free_acl(SMB_ACL_T the_acl)
{
	return acl_free(the_acl);
}