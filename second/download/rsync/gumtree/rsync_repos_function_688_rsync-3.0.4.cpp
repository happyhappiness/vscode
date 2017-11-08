int sys_acl_delete_def_file(const char *name)
{
	return acl_delete_def_file((char *)name);
}