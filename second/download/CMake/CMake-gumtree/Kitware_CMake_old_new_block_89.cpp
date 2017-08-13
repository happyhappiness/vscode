{
	case 01000000:
		/* POSIX.1e ACL */
		break;
	case 03000000:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Solaris NFSv4 ACLs not supported");
		return (ARCHIVE_WARN);
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Malformed Solaris ACL attribute (unsupported type %o)",
		    (int)type);
		return (ARCHIVE_WARN);
	}