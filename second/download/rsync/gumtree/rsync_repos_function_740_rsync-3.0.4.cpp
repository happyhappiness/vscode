int sys_acl_set_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T tag_type, uint32 bits, id_t u_g_id)
{
	entry->ace_id->id_type = tag_type;
	DEBUG(10,("The tag type is %d\n",entry->ace_id->id_type));

	if (tag_type == SMB_ACL_USER || tag_type == SMB_ACL_GROUP)
		memcpy(entry->ace_id->id_data, &u_g_id, sizeof (id_t));

	entry->ace_access = bits;
	DEBUG(10,("entry->ace_access = %d\n",entry->ace_access));

	return 0;
}