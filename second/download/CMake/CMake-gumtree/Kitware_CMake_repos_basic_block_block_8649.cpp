h(*p++) {
		case L'f':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT;
			break;
		case L'd':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT;
			break;
		case L'i':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY;
			break;
		case L'n':
			*permset |=
			    ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT;
			break;
		case L'S':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS;
			break;
		case L'F':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS;
			break;
		case L'I':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_INHERITED;
			break;
		case L'-':
			break;
		default:
			return (0);
		}