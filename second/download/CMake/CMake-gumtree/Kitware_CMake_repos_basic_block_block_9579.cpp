(acl_get_flagset_np(acl_entry, &acl_flagset) != 0) {
				archive_set_error(&a->archive, errno,
				    "Failed to get flagset from a NFSv4 ACL entry");
				return (ARCHIVE_WARN);
			}