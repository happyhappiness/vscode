(r == -1) {
				archive_set_error(&a->archive, errno,
				    "Failed to check permission in an ACL permission set");
				return (ARCHIVE_WARN);
			} else if (r)
				ae_perm |= acl_perm_map[i].archive_perm