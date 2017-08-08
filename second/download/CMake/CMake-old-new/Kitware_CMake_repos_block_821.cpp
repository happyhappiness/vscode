{
		case BZ_STREAM_END: /* Found end of stream. */
			switch (BZ2_bzDecompressEnd(&(zip->bzstream))) {
			case BZ_OK:
				break;
			default:
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Failed to clean up decompressor");
				return (ARCHIVE_FAILED);
			}
			zip->bzstream_valid = 0;
			ret = ARCHIVE_EOF;
			break;
		case BZ_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "bzip decompression failed");
			return (ARCHIVE_FAILED);
		}