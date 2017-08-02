{
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
			"Invalid ACL type");
		acl_free(acl);
		return (ARCHIVE_FAILED);
	}