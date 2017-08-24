(i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
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