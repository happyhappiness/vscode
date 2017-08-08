{
	case Z_OK:
		break;
	default:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Failed to clean up gzip decompressor");
		return (ARCHIVE_FATAL);
	}