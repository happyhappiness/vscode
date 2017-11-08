int sys_acl_set_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T tag_type, uint32 bits, id_t u_g_id)
{
	if (acl_set_tag_type(entry, tag_type) != 0)
		return -1;

	if (tag_type == SMB_ACL_USER || tag_type == SMB_ACL_GROUP) {
		if (acl_set_qualifier(entry, (void*)&u_g_id) != 0)
			return -1;
	}

	return sys_acl_set_access_bits(entry, bits);
}