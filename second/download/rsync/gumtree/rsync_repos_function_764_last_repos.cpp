int sys_acl_set_access_bits(SMB_ACL_ENTRY_T entry, uint32 bits)
{
	acl_permset_t permset;
	int rc;
	if ((rc = acl_get_permset(entry, &permset)) != 0)
		return rc;
	*permset = bits & 7;
	return acl_set_permset(entry, permset);
}