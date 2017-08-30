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



