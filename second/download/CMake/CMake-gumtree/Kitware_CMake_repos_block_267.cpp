{
		case LZMA_STREAM_END: /* Found end of stream. */
			lzma_end(&(xar->lzstream));
			xar->lzstream_valid = 0;
			/* FALLTHROUGH */
		case LZMA_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "%s decompression failed(%d)",
			    (xar->entry_encoding == XZ)?"xz":"lzma",
			    r);
			return (ARCHIVE_FATAL);
		}