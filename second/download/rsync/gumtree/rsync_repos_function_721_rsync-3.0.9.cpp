int sys_acl_set_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T tag_type, uint32 bits, id_t u_g_id)
{
	entry->a_type = tag_type;

	if (tag_type == SMB_ACL_USER || tag_type == SMB_ACL_GROUP)
		entry->a_id = u_g_id;

	entry->a_perm = bits;

	return 0;
}