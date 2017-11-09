int sys_acl_get_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T *tag_type_p, uint32 *bits_p, id_t *u_g_id_p)
{
	uint *permset;

	if (sys_acl_get_tag_type(entry, tag_type_p) != 0)
		return -1;

	if (*tag_type_p == SMB_ACL_USER || *tag_type_p == SMB_ACL_GROUP)
		memcpy(u_g_id_p, entry->ace_id->id_data, sizeof (id_t));

	permset = &entry->ace_access;

	DEBUG(10,("*permset is %d\n",*permset));
	*bits_p = (*permset & S_IRUSR ? 4 : 0)
		| (*permset & S_IWUSR ? 2 : 0)
		| (*permset & S_IXUSR ? 1 : 0);

	return 0;
}