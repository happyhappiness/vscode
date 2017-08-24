(i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
			if (ae_permset & acl_perm_map[i].archive_perm) {
#if HAVE_SUN_ACL
				ace->a_access_mask |=
				    acl_perm_map[i].platform_perm;
#else
				if (acl_add_perm(acl_permset,
				    acl_perm_map[i].platform_perm) != 0) {
					archive_set_error(a, errno,
					    "Failed to add ACL permission");
					ret = ARCHIVE_FAILED;
					goto exit_free;
				}
#endif
			}
		}