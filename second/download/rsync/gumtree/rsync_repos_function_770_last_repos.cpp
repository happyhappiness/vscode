int sys_acl_get_tag_type(SMB_ACL_ENTRY_T entry_d, SMB_ACL_TAG_T *type_p)
{
	*type_p = entry_d->a_type;

	return 0;
}