{
		case BZ_STREAM_END: /* Found end of stream. */
			switch (BZ2_bzDecompressEnd(&(xar->bzstream))) {
			case BZ_OK:
				break;
			default:
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Failed to clean up decompressor");
				return (ARCHIVE_FATAL);
			}
			xar->bzstream_valid = 0;
			/* FALLTHROUGH */
		case BZ_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "bzip decompression failed");
			return (ARCHIVE_FATAL);
		}