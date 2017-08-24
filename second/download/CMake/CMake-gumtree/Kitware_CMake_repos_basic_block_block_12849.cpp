{
	case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
		errstr = "SCHILY.acl.access";
		break;
	case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
		errstr = "SCHILY.acl.default";
		break;
	case ARCHIVE_ENTRY_ACL_TYPE_NFS4:
		errstr = "SCHILY.acl.ace";
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Unknown ACL type: %d", type);
		return(ARCHIVE_FATAL);
	}