SMB_ACL_T sys_acl_get_file(const char *path_p, SMB_ACL_TYPE_T type)
{
	if (type == ACL_TYPE_DEFAULT) {
		errno = ENOTSUP;
		return NULL;
	}
	errno = 0;
	return acl_get_file(path_p, type);
}