(i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
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