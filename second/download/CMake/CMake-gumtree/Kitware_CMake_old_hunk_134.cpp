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

