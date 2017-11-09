int sys_acl_get_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T *tag_type_p, uint32 *bits_p, id_t *u_g_id_p)
{
	acl_permset_t permset;

	if (acl_get_tag_type(entry, tag_type_p) != 0
	 || acl_get_permset(entry, &permset) != 0)
		return -1;

	*bits_p = *permset & 7;	/* Tru64 doesn't have acl_get_perm() */

	if (*tag_type_p == SMB_ACL_USER || *tag_type_p == SMB_ACL_GROUP) {
		void *qual;
		if ((qual = acl_get_qualifier(entry)) == NULL)
			return -1;
		*u_g_id_p = *(id_t*)qual;
		acl_free_qualifier(qual, *tag_type_p);
	}

	return 0;
}