static int store_access_in_entry(uint32 access, SMB_ACL_ENTRY_T entry)
{
	if (sys_acl_set_access_bits(entry, access)) {
		rsyserr(FERROR_XFER, errno, "store_access_in_entry sys_acl_set_access_bits()");
		return -1;
	}
	return 0;
}