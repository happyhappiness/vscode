int sys_acl_set_access_bits(SMB_ACL_ENTRY_T entry, uint32 bits)
{
	acl_permset_t permset;
	int rc;
	if ((rc = acl_get_permset(entry, &permset)) != 0)
		return rc;
	acl_clear_perms(permset);
	if (bits & 4)
		acl_add_perm(permset, ACL_READ);
	if (bits & 2)
		acl_add_perm(permset, ACL_WRITE);
	if (bits & 1)
		acl_add_perm(permset, ACL_EXECUTE);
	return acl_set_permset(entry, permset);
}