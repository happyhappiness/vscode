int sys_acl_get_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T *tag_type_p, uint32 *bits_p, id_t *u_g_id_p)
{
	*tag_type_p = entry->ae_tag;

	*bits_p = entry->ae_perm;

	if (*tag_type_p == SMB_ACL_USER || *tag_type_p == SMB_ACL_GROUP)
		*u_g_id_p = entry->ae_id;

	return 0;
}