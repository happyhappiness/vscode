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

