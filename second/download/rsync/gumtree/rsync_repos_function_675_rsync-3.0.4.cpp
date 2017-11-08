int sys_acl_set_file(const char *name, SMB_ACL_TYPE_T acltype, SMB_ACL_T theacl)
{
	return acl_set_file(name, acltype, theacl);
}