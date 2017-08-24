(tag) {
	case ARCHIVE_ENTRY_ACL_USER:
	case ARCHIVE_ENTRY_ACL_USER_OBJ:
	case ARCHIVE_ENTRY_ACL_GROUP:
	case ARCHIVE_ENTRY_ACL_GROUP_OBJ:
		/* Tags valid in both NFS4 and POSIX.1e */
		break;
	case ARCHIVE_ENTRY_ACL_MASK:
	case ARCHIVE_ENTRY_ACL_OTHER:
		/* Tags valid only in POSIX.1e. */
		if (type & ~ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) {
			return (NULL);
		}
		break;
	case ARCHIVE_ENTRY_ACL_EVERYONE:
		/* Tags valid only in NFS4. */
		if (type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
			return (NULL);
		}
		break;
	default:
		/* No other values are valid. */
		return (NULL);
	}