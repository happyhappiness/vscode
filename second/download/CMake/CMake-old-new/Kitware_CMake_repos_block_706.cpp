{
	case Z_OK:
		break;
	default:
	case Z_STREAM_ERROR:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing "
		    "compression library: invalid setup parameter");
		return (ARCHIVE_FATAL);
	case Z_MEM_ERROR:
		archive_set_error(&a->archive, ENOMEM,
		    "Internal error initializing "
		    "compression library");
		return (ARCHIVE_FATAL);
	case Z_VERSION_ERROR:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing "
		    "compression library: invalid library version");
		return (ARCHIVE_FATAL);
	}