{
		case LZMADEC_STREAM_END: /* Found end of stream. */
			switch (lzmadec_end(&(xar->lzstream))) {
			case LZMADEC_OK:
				break;
			default:
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Failed to clean up lzmadec decompressor");
				return (ARCHIVE_FATAL);
			}
			xar->lzstream_valid = 0;
			/* FALLTHROUGH */
		case LZMADEC_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "lzmadec decompression failed(%d)",
			    r);
			return (ARCHIVE_FATAL);
		}