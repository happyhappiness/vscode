SMB_ACL_T sys_acl_get_file( const char *path_p, SMB_ACL_TYPE_T type)
{
	return acl_get_file( path_p, type);
}