(i = 0; i < (int)(sizeof(acl_inherit_map) /
			    sizeof(acl_inherit_map[0])); ++i) {
				if ((ace->a_flags &
				    acl_inherit_map[i].platform_inherit) != 0)
					ae_perm |=
					    acl_inherit_map[i].archive_inherit;
			}