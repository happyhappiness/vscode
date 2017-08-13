{
		case Z_OK: /* Decompressor made some progress. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			break;
		case Z_STREAM_END: /* Found end of stream. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			/* Consume the stream trailer; release the
			 * decompression library. */
			ret = consume_trailer(self);
			if (ret < ARCHIVE_OK)
				return (ret);
			break;
		default:
			/* Return an error. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "gzip decompression failed");
			return (ARCHIVE_FATAL);
		}