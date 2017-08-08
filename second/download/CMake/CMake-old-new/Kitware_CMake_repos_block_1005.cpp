{
	case Z_OK:
		return (ARCHIVE_OK);
	case Z_STREAM_END:
		return (ARCHIVE_EOF);
	default:
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "GZip compression failed:"
		    " deflate() call returned status %d", r);
		return (ARCHIVE_FATAL);
	}