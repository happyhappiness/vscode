{
		ae_id = -1;
		ae_name = NULL;
		ae_perm = 0;

		if (acl_get_tag_type(acl_entry, &acl_tag) != 0) {
			archive_set_error(&a->archive, errno,
			    "Failed to get ACL tag type");
			return (ARCHIVE_WARN);
		}
		switch (acl_tag) {
#if !HAVE_DARWIN_ACL	/* FreeBSD, Linux */
		case ACL_USER:
			q = acl_get_qualifier(acl_entry);
			if (q != NULL) {
				ae_id = (int)*(uid_t *)q;
				acl_free(q);
				ae_name = archive_read_disk_uname(&a->archive,
				    ae_id);
			}
			ae_tag = ARCHIVE_ENTRY_ACL_USER;
			break;
		case ACL_GROUP:
			q = acl_get_qualifier(acl_entry);
			if (q != NULL) {
				ae_id = (int)*(gid_t *)q;
				acl_free(q);
				ae_name = archive_read_disk_gname(&a->archive,
				    ae_id);
			}
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
#if HAVE_ACL_TYPE_NFS4
		case ACL_EVERYONE:
			ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
			break;
#endif
#else	/* HAVE_DARWIN_ACL */
		case ACL_EXTENDED_ALLOW:
			entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
			r = translate_guid(&a->archive, acl_entry, &ae_id,
			    &ae_tag, &ae_name);
			break;
		case ACL_EXTENDED_DENY:
			entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
			r = translate_guid(&a->archive, acl_entry, &ae_id,
			    &ae_tag, &ae_name);
			break;
#endif	/* HAVE_DARWIN_ACL */
		default:
			/* Skip types that libarchive can't support. */
			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
			continue;
		}

#if HAVE_DARWIN_ACL
		/* Skip if translate_guid() above failed */
		if (r != 0) {
			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
			continue;
		}
#endif

#if !HAVE_DARWIN_ACL
		// XXX acl_type maps to allow/deny/audit/YYYY bits
		entry_acl_type = default_entry_acl_type;
#endif
#if HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL
		if (default_entry_acl_type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
#if HAVE_ACL_TYPE_NFS4
			/*
			 * acl_get_entry_type_np() fails with non-NFSv4 ACLs
			 */
			if (acl_get_entry_type_np(acl_entry, &acl_type) != 0) {
				archive_set_error(&a->archive, errno, "Failed "
				    "to get ACL type from a NFSv4 ACL entry");
				return (ARCHIVE_WARN);
			}
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
			default:
				archive_set_error(&a->archive, errno,
				    "Invalid NFSv4 ACL entry type");
				return (ARCHIVE_WARN);
			}
#endif	/* HAVE_ACL_TYPE_NFS4 */

			/*
			 * Libarchive stores "flag" (NFSv4 inheritance bits)
			 * in the ae_perm bitmap.
			 *
			 * acl_get_flagset_np() fails with non-NFSv4 ACLs
			 */
			if (acl_get_flagset_np(acl_entry, &acl_flagset) != 0) {
				archive_set_error(&a->archive, errno,
				    "Failed to get flagset from a NFSv4 ACL entry");
				return (ARCHIVE_WARN);
			}
			for (i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
				r = acl_get_flag_np(acl_flagset,
				    acl_inherit_map[i].platform_inherit);
				if (r == -1) {
					archive_set_error(&a->archive, errno,
					    "Failed to check flag in a NFSv4 "
					    "ACL flagset");
					return (ARCHIVE_WARN);
				} else if (r)
					ae_perm |= acl_inherit_map[i].archive_inherit;
			}
		}
#endif	/* HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL */

		if (acl_get_permset(acl_entry, &acl_permset) != 0) {
			archive_set_error(&a->archive, errno,
			    "Failed to get ACL permission set");
			return (ARCHIVE_WARN);
		}
		for (i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
			/*
			 * acl_get_perm() is spelled differently on different
			 * platforms; see above.
			 */
			r = ACL_GET_PERM(acl_permset, acl_perm_map[i].platform_perm);
			if (r == -1) {
				archive_set_error(&a->archive, errno,
				    "Failed to check permission in an ACL permission set");
				return (ARCHIVE_WARN);
			} else if (r)
				ae_perm |= acl_perm_map[i].archive_perm;
		}

		archive_entry_acl_add_entry(entry, entry_acl_type,
					    ae_perm, ae_tag,
					    ae_id, ae_name);

		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
#if !HAVE_DARWIN_ACL
		if (s == -1) {
			archive_set_error(&a->archive, errno,
			    "Failed to get next ACL entry");
			return (ARCHIVE_WARN);
		}
#endif
	}