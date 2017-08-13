{
		case ARCHIVE_OK:
		case ARCHIVE_EOF:
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "LZX decompression failed (%d)", r);
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}