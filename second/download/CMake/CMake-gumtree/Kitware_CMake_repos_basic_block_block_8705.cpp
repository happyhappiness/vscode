{
	case ARCHIVE_STATE_NEW:		return ("new");
	case ARCHIVE_STATE_HEADER:	return ("header");
	case ARCHIVE_STATE_DATA:	return ("data");
	case ARCHIVE_STATE_EOF:		return ("eof");
	case ARCHIVE_STATE_CLOSED:	return ("closed");
	case ARCHIVE_STATE_FATAL:	return ("fatal");
	default:			return ("??");
	}