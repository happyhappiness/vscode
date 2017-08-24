(*p++) {
		case 'r': case 'R':
			*permset |= ARCHIVE_ENTRY_ACL_READ;
			break;
		case 'w': case 'W':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE;
			break;
		case 'x': case 'X':
			*permset |= ARCHIVE_ENTRY_ACL_EXECUTE;
			break;
		case '-':
			break;
		default:
			return (0);
		}