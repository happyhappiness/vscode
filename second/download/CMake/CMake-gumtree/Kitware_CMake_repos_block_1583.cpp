{
	case ARCHIVE_OK:
		break;
	case ARCHIVE_EOF:
		lha->end_of_entry = 1;
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Bad lzh data");
		return (ARCHIVE_FAILED);
	}