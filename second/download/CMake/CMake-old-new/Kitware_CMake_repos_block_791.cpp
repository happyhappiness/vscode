{
		case LZMA_STREAM_END: /* Found end of stream. */
			lzma_end(&(zip->lzstream));
			zip->lzstream_valid = 0;
			ret = ARCHIVE_EOF;
			break;
		case LZMA_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
				"Decompression failed(%d)",
			    r);
			return (ARCHIVE_FAILED);
		}