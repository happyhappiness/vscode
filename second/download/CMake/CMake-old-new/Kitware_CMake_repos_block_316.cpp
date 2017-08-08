{
		case Z_OK:
		case Z_STREAM_END:
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Failed to compress data");
			return (ARCHIVE_FAILED);
		}