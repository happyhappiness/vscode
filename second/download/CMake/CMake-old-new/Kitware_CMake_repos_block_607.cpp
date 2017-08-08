{
	case BZ_OK:
		break;
	default:
		archive_set_error(f->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Failed to clean up compressor");
		ret = ARCHIVE_FATAL;
	}