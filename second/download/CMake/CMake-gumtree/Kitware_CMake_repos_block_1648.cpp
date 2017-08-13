{
	case iFoldCONTINUED_FROM_PREV:
	case iFoldCONTINUED_TO_NEXT:
	case iFoldCONTINUED_PREV_AND_NEXT:
		*buff = NULL;
		*size = 0;
		*offset = 0;
		archive_clear_error(&a->archive);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Cannot restore this file split in multivolume.");
		return (ARCHIVE_FAILED);
	default:
		break;
	}