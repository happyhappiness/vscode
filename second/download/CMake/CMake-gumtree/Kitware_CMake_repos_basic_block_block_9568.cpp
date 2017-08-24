{
		ae_name = NULL;
		ae_tag = 0;
		ae_perm = 0;

		if (acl->acl_type == ACE_T) {
			ace = &((ace_t *)acl->acl_aclp)[e];
			ae_id = ace->a_who;

			switch(ace->a_type) {
			case ACE_ACCESS_ALLOWED_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
				break;
			case ACE_ACCESS_DENIED_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
				break;
			case ACE_SYSTEM_AUDIT_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
				break;
			case ACE_SYSTEM_ALARM_ACE_TYPE:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
				break;
			default:
				/* Unknown entry type, skip */
				continue;
			}

			if ((ace->a_flags & ACE_OWNER) != 0)
				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
			else if ((ace->a_flags & ACE_GROUP) != 0)
				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
			else if ((ace->a_flags & ACE_EVERYONE) != 0)
				ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
			else if ((ace->a_flags & ACE_IDENTIFIER_GROUP) != 0) {
				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
				ae_name = archive_read_disk_gname(&a->archive,
				    ae_id);
			} else {
				ae_tag = ARCHIVE_ENTRY_ACL_USER;
				ae_name = archive_read_disk_uname(&a->archive,
				    ae_id);
			}

			for (i = 0; i < (int)(sizeof(acl_inherit_map) /
			    sizeof(acl_inherit_map[0])); ++i) {
				if ((ace->a_flags &
				    acl_inherit_map[i].platform_inherit) != 0)
					ae_perm |=
					    acl_inherit_map[i].archive_inherit;
			}

			for (i = 0; i < (int)(sizeof(acl_perm_map) /
			    sizeof(acl_perm_map[0])); ++i) {
				if ((ace->a_access_mask &
				    acl_perm_map[i].platform_perm) != 0)
					ae_perm |=
					    acl_perm_map[i].archive_perm;
			}
		} else {
			aclent = &((aclent_t *)acl->acl_aclp)[e];
			if ((aclent->a_type & ACL_DEFAULT) != 0)
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DEFAULT;
			else
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
			ae_id = aclent->a_id;

			switch(aclent->a_type) {
			case DEF_USER:
			case USER:
				ae_name = archive_read_disk_uname(&a->archive,
				    ae_id);
				ae_tag = ARCHIVE_ENTRY_ACL_USER;
				break;
			case DEF_GROUP:
			case GROUP:
				ae_name = archive_read_disk_gname(&a->archive,
				    ae_id);
				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
				break;
			case DEF_CLASS_OBJ:
			case CLASS_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_MASK;
				break;
			case DEF_USER_OBJ:
			case USER_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
				break;
			case DEF_GROUP_OBJ:
			case GROUP_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
				break;
			case DEF_OTHER_OBJ:
			case OTHER_OBJ:
				ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
				break;
			default:
				/* Unknown tag type, skip */
				continue;
			}

			if ((aclent->a_perm & 1) != 0)
				ae_perm |= ARCHIVE_ENTRY_ACL_EXECUTE;
			if ((aclent->a_perm & 2) != 0)
				ae_perm |= ARCHIVE_ENTRY_ACL_WRITE;
			if ((aclent->a_perm & 4) != 0)
				ae_perm |= ARCHIVE_ENTRY_ACL_READ;
		} /* default_entry_acl_type != ARCHIVE_ENTRY_ACL_TYPE_NFS4 */

		archive_entry_acl_add_entry(entry, entry_acl_type,
		    ae_perm, ae_tag, ae_id, ae_name);
	}