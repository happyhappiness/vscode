{
		case 'f':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT;
			break;
		case 'd':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT;
			break;
		case 'i':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY;
			break;
		case 'n':
			*permset |=
			    ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT;
			break;
		case 'S':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS;
			break;
		case 'F':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS;
			break;
		case 'I':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_INHERITED;
			break;
		case '-':
			break;
		default:
			return (0);
		}