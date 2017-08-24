{
		case ARCHIVE_FORMAT_CPIO_SVR4_NOCRC:
		case ARCHIVE_FORMAT_CPIO_SVR4_CRC:
			res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_NEW_CPIO;
			break;
		default:
			res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
			break;
		}