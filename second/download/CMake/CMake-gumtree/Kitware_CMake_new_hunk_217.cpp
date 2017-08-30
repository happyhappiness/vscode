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
