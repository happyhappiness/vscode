(type & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) {
		if (acl->acl_types & ~ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) {
			return (NULL);
		}
		if (permset & ~ARCHIVE_ENTRY_ACL_PERMS_POSIX1E) {
			return (NULL);
		}
	}