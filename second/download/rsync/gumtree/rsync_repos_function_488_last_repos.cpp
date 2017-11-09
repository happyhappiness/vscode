static BOOL unpack_smb_acl(SMB_ACL_T sacl, rsync_acl *racl)
{
	static item_list temp_ida_list = EMPTY_ITEM_LIST;
	SMB_ACL_ENTRY_T entry;
	const char *errfun;
	int rc;

	errfun = "sys_acl_get_entry";
	for (rc = sys_acl_get_entry(sacl, SMB_ACL_FIRST_ENTRY, &entry);
	     rc == 1;
	     rc = sys_acl_get_entry(sacl, SMB_ACL_NEXT_ENTRY, &entry)) {
		SMB_ACL_TAG_T tag_type;
		uint32 access;
		id_t g_u_id;
		id_access *ida;
		if ((rc = sys_acl_get_info(entry, &tag_type, &access, &g_u_id)) != 0) {
			errfun = "sys_acl_get_info";
			break;
		}
		/* continue == done with entry; break == store in temporary ida list */
		switch (tag_type) {
#ifndef HAVE_OSX_ACLS
		case SMB_ACL_USER_OBJ:
			if (racl->user_obj == NO_ENTRY)
				racl->user_obj = access;
			else
				rprintf(FINFO, "unpack_smb_acl: warning: duplicate USER_OBJ entry ignored\n");
			continue;
		case SMB_ACL_GROUP_OBJ:
			if (racl->group_obj == NO_ENTRY)
				racl->group_obj = access;
			else
				rprintf(FINFO, "unpack_smb_acl: warning: duplicate GROUP_OBJ entry ignored\n");
			continue;
		case SMB_ACL_MASK:
			if (racl->mask_obj == NO_ENTRY)
				racl->mask_obj = access;
			else
				rprintf(FINFO, "unpack_smb_acl: warning: duplicate MASK entry ignored\n");
			continue;
		case SMB_ACL_OTHER:
			if (racl->other_obj == NO_ENTRY)
				racl->other_obj = access;
			else
				rprintf(FINFO, "unpack_smb_acl: warning: duplicate OTHER entry ignored\n");
			continue;
#endif
		case SMB_ACL_USER:
			access |= NAME_IS_USER;
			break;
		case SMB_ACL_GROUP:
			break;
		default:
			rprintf(FINFO, "unpack_smb_acl: warning: entry with unrecognized tag type ignored\n");
			continue;
		}
		ida = EXPAND_ITEM_LIST(&temp_ida_list, id_access, -10);
		ida->id = g_u_id;
		ida->access = access;
	}
	if (rc) {
		rsyserr(FERROR_XFER, errno, "unpack_smb_acl: %s()", errfun);
		rsync_acl_free(racl);
		return False;
	}

	/* Transfer the count id_access items out of the temp_ida_list
	 * into the names ida_entries list in racl. */
	if (temp_ida_list.count) {
#ifdef SMB_ACL_NEED_SORT
		if (temp_ida_list.count > 1) {
			qsort(temp_ida_list.items, temp_ida_list.count,
			      sizeof (id_access), id_access_sorter);
		}
#endif
		if (!(racl->names.idas = new_array(id_access, temp_ida_list.count)))
			out_of_memory("unpack_smb_acl");
		memcpy(racl->names.idas, temp_ida_list.items,
		       temp_ida_list.count * sizeof (id_access));
	} else
		racl->names.idas = NULL;

	racl->names.count = temp_ida_list.count;

	/* Truncate the temporary list now that its idas have been saved. */
	temp_ida_list.count = 0;

	return True;
}