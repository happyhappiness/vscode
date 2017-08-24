(brand) {
	case ACL_BRAND_POSIX:
		switch (default_entry_acl_type) {
		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid ACL entry type for POSIX.1e ACL");
			return (ARCHIVE_WARN);
		}
		break;
	case ACL_BRAND_NFS4:
		if (default_entry_acl_type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid ACL entry type for NFSv4 ACL");
			return (ARCHIVE_WARN);
		}
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Unknown ACL brand");
		return (ARCHIVE_WARN);
	}