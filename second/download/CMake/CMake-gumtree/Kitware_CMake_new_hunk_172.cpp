	switch ((int)type & ~0777777) {
	case 01000000:
		/* POSIX.1e ACL */
		acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
		break;
	case 03000000:
		/* NFSv4 ACL */
		acl_type = ARCHIVE_ENTRY_ACL_TYPE_NFS4;
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Malformed Solaris ACL attribute (unsupported type %o)",
