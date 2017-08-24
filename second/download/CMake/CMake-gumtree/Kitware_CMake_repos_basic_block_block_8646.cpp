(*p++) {
		case L'r': case L'R':
			*permset |= ARCHIVE_ENTRY_ACL_READ;
			break;
		case L'w': case L'W':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE;
			break;
		case L'x': case L'X':
			*permset |= ARCHIVE_ENTRY_ACL_EXECUTE;
			break;
		case L'-':
			break;
		default:
			return (0);
		}