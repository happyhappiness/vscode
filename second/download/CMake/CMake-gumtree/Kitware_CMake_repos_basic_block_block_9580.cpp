(acl_get_entry_type_np(acl_entry, &acl_type) != 0) {
				archive_set_error(&a->archive, errno, "Failed "
				    "to get ACL type from a NFSv4 ACL entry");
				return (ARCHIVE_WARN);
			}