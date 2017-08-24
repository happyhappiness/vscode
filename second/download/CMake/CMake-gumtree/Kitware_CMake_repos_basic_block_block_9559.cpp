(i = 0; i < (int)(sizeof(acl_perm_map) /
			    sizeof(acl_perm_map[0])); ++i) {
				if ((ace->a_access_mask &
				    acl_perm_map[i].platform_perm) != 0)
					ae_perm |=
					    acl_perm_map[i].archive_perm;
			}