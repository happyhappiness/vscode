int sys_acl_get_entry(SMB_ACL_T the_acl, int entry_id, SMB_ACL_ENTRY_T *entry_p)
{
	int ret = acl_get_entry(the_acl, entry_id, entry_p);
#ifdef OSX_BROKEN_GETENTRY
	if (ret == 0)
		ret = 1;
	else if (ret == -1 && errno == 22)
		ret = 0;
#endif
	return ret;
}