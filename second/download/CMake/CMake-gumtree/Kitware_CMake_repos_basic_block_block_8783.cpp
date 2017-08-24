{
	case ARCHIVE_FORMAT_7ZIP:
	case ARCHIVE_FORMAT_AR:
	case ARCHIVE_FORMAT_ZIP:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
		break;
	case ARCHIVE_FORMAT_CPIO:
		switch (fmt) {
		case ARCHIVE_FORMAT_CPIO_SVR4_NOCRC:
		case ARCHIVE_FORMAT_CPIO_SVR4_CRC:
			res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_NEW_CPIO;
			break;
		default:
			res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
			break;
		}
		break;
	case ARCHIVE_FORMAT_MTREE:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_MTREE;
		break;
	case ARCHIVE_FORMAT_ISO9660:
	case ARCHIVE_FORMAT_SHAR:
	case ARCHIVE_FORMAT_TAR:
	case ARCHIVE_FORMAT_XAR:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_TAR;
		break;
	default:
		res->strategy = ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO;
		break;
	}