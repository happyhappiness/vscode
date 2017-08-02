{
	case 0x0001: /* Password is required to decrypt. */
	case 0x0002: /* Certificates only. */
	case 0x0003: /* Password or certificate required to decrypt. */
		break;
	default:
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unknown encryption flag: %u", zip->flags);
		return (ARCHIVE_FAILED);
	}