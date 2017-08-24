(deflateEnd(&a->stream)) {
		case Z_OK:
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Failed to clean up compressor");
			ret = ARCHIVE_FATAL;
			break;
		}