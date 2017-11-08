int sys_acl_set_info(SMB_ACL_ENTRY_T entry, SMB_ACL_TAG_T tag_type, uint32 bits, id_t u_g_id)
{
	acl_flagset_t flagset;
	acl_permset_t permset;
	uint32 fb, bb, pb;
	int is_user = tag_type == SMB_ACL_USER;
	uuid_t uu;
	int rc;

	tag_type = bits & 1 ? ACL_EXTENDED_ALLOW : ACL_EXTENDED_DENY;

	if (acl_get_flagset_np(entry, &flagset) != 0
	 || acl_get_permset(entry, &permset) != 0)
		return -1;

	acl_clear_flags_np(flagset);
	acl_clear_perms(permset);

	for (fb = (1u<<4), bb = (1u<<1); bb < (1u<<12); fb *= 2, bb *= 2) {
		if (bits & bb)
			acl_add_flag_np(flagset, fb);
	}

	for (pb = (1u<<1), bb = (1u<<12); bb < (1u<<25); pb *= 2, bb *= 2) {
		if (bits & bb)
			acl_add_perm(permset, pb);
	}

	if (is_user)
		rc = mbr_uid_to_uuid(u_g_id, uu);
	else
		rc = mbr_gid_to_uuid(u_g_id, uu);
	if (rc != 0)
		return rc;

	if (acl_set_tag_type(entry, tag_type) != 0
	 || acl_set_qualifier(entry, &uu) != 0
	 || acl_set_permset(entry, permset) != 0
	 || acl_set_flagset_np(entry, flagset) != 0)
		return -1;

	return 0;
}