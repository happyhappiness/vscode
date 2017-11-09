SMB_ACL_T sys_acl_get_file(const char *path_p, SMB_ACL_TYPE_T type)
{
	SMB_ACL_T	a;

	if ((a = SMB_MALLOC_P(struct SMB_ACL_T)) == NULL) {
		errno = ENOMEM;
		return NULL;
	}
	if ((a->aclp = acl_get_file(path_p, type)) == NULL) {
		SAFE_FREE(a);
		return NULL;
	}
	a->next = -1;
	a->freeaclp = True;
	return a;
}