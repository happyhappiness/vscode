static int
translate_acl(struct archive_read_disk *a,
    struct archive_entry *entry, acl_t acl, int default_entry_acl_type)
{
	acl_tag_t	 acl_tag;
#ifdef ACL_TYPE_NFS4
	acl_entry_type_t acl_type;
	acl_flagset_t	 acl_flagset;
	int brand, r;
#endif
	acl_entry_t	 acl_entry;
	acl_permset_t	 acl_permset;
	int		 i, entry_acl_type;
	int		 s, ae_id, ae_tag, ae_perm;
	const char	*ae_name;


#ifdef ACL_TYPE_NFS4
	// FreeBSD "brands" ACLs as POSIX.1e or NFSv4
	// Make sure the "brand" on this ACL is consistent
	// with the default_entry_acl_type bits provided.
	acl_get_brand_np(acl, &brand);
	switch (brand) {
	case ACL_BRAND_POSIX:
		switch (default_entry_acl_type) {
		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
			break;
		default:
			// XXX set warning message?
			return ARCHIVE_FAILED;
		}
		break;
	case ACL_BRAND_NFS4:
		if (default_entry_acl_type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
			// XXX set warning message?
			return ARCHIVE_FAILED;
		}
		break;
	default:
		// XXX set warning message?
		return ARCHIVE_FAILED;
		break;
	}
#endif


	s = acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry);
	while (s == 1) {
		ae_id = -1;
		ae_name = NULL;
		ae_perm = 0;

		acl_get_tag_type(acl_entry, &acl_tag);
		switch (acl_tag) {
		case ACL_USER:
			ae_id = (int)*(uid_t *)acl_get_qualifier(acl_entry);
			ae_name = archive_read_disk_uname(&a->archive, ae_id);
			ae_tag = ARCHIVE_ENTRY_ACL_USER;
			break;
		case ACL_GROUP:
			ae_id = (int)*(gid_t *)acl_get_qualifier(acl_entry);
			ae_name = archive_read_disk_gname(&a->archive, ae_id);
			ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
			break;
		case ACL_MASK:
			ae_tag = ARCHIVE_ENTRY_ACL_MASK;
			break;
		case ACL_USER_OBJ:
			ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
			break;
		case ACL_GROUP_OBJ:
			ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
			break;
		case ACL_OTHER:
			ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
			break;
#ifdef ACL_TYPE_NFS4
		case ACL_EVERYONE:
			ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
			break;
#endif
		default:
			/* Skip types that libarchive can't support. */
			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
			continue;
		}

		// XXX acl type maps to allow/deny/audit/YYYY bits
		// XXX acl_get_entry_type_np on FreeBSD returns EINVAL for
		// non-NFSv4 ACLs
		entry_acl_type = default_entry_acl_type;
#ifdef ACL_TYPE_NFS4
		r = acl_get_entry_type_np(acl_entry, &acl_type);
		if (r == 0) {
			switch (acl_type) {
			case ACL_ENTRY_TYPE_ALLOW:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
				break;
			case ACL_ENTRY_TYPE_DENY:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
				break;
			case ACL_ENTRY_TYPE_AUDIT:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_AUDIT;
				break;
			case ACL_ENTRY_TYPE_ALARM:
				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
				break;
			}
		}

		/*
		 * Libarchive stores "flag" (NFSv4 inheritance bits)
		 * in the ae_perm bitmap.
		 */
		acl_get_flagset_np(acl_entry, &acl_flagset);
                for (i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
			if (acl_get_flag_np(acl_flagset,
					    acl_inherit_map[i].platform_inherit))
				ae_perm |= acl_inherit_map[i].archive_inherit;

                }
#endif

		acl_get_permset(acl_entry, &acl_permset);
		for (i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
			/*
			 * acl_get_perm() is spelled differently on different
			 * platforms; see above.
			 */
			if (ACL_GET_PERM(acl_permset, acl_perm_map[i].platform_perm))
				ae_perm |= acl_perm_map[i].archive_perm;
		}

		archive_entry_acl_add_entry(entry, entry_acl_type,
					    ae_perm, ae_tag,
					    ae_id, ae_name);

		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
	}
	return (ARCHIVE_OK);
}