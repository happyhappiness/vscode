int sys_acl_set_access_bits(SMB_ACL_ENTRY_T entry_d, uint32 bits)
{
	entry_d->a_perm = bits;
	return 0;
}