int sys_acl_set_file(const char *name, SMB_ACL_TYPE_T type, SMB_ACL_T acl_d)
{
	return acl_set_file(name, type, acl_d->aclp);
}