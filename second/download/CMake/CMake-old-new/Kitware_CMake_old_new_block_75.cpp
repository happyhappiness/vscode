{
		case LZMADEC_STREAM_END: /* Found end of stream. */
			state->eof = 1;
			/* FALL THROUGH */
		case LZMADEC_OK: /* Decompressor made some progress. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			break;
		case LZMADEC_BUF_ERROR: /* Insufficient input data? */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Insufficient compressed data");
			return (ARCHIVE_FATAL);
		default:
			/* Return an error. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Lzma decompression failed");
			return (ARCHIVE_FATAL);
		}