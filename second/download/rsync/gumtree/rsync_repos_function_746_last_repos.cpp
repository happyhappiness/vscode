int sys_acl_get_tag_type( SMB_ACL_ENTRY_T entry_d, SMB_ACL_TAG_T *tag_type_p)
{
	return acl_get_tag_type( entry_d, tag_type_p);
}