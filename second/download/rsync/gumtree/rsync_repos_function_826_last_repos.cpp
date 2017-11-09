int sys_acl_get_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T *tag_type_p, uint32 *bits_p, id_t *u_g_id_p)
{
	uuid_t *uup;
	acl_tag_t tag;
	acl_flagset_t flagset;
	acl_permset_t permset;
	uint32 bits, fb, bb, pb;
	int id_type = -1;
	int rc;

	if (acl_get_tag_type(entry, &tag) != 0
	 || acl_get_flagset_np(entry, &flagset) != 0
	 || acl_get_permset(entry, &permset) != 0
	 || (uup = acl_get_qualifier(entry)) == NULL)
		return -1;

	rc = mbr_uuid_to_id(*uup, u_g_id_p, &id_type);
	acl_free(uup);
	if (rc != 0)
		return rc;

	if (id_type == ID_TYPE_UID)
		*tag_type_p = SMB_ACL_USER;
	else
		*tag_type_p = SMB_ACL_GROUP;

	bits = tag == ACL_EXTENDED_ALLOW ? 1 : 0;

	for (fb = (1u<<4), bb = (1u<<1); bb < (1u<<12); fb *= 2, bb *= 2) {
		if (acl_get_flag_np(flagset, fb) == 1)
			bits |= bb;
	}

	for (pb = (1u<<1), bb = (1u<<12); bb < (1u<<25); pb *= 2, bb *= 2) {
		if (acl_get_perm_np(permset, pb) == 1)
			bits |= bb;
	}

	*bits_p = bits;

	return 0;
}