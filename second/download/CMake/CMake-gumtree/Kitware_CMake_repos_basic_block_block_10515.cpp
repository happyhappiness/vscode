{
		case LZMA_STREAM_END: /* Found end of stream. */
			state->eof = 1;
			/* FALL THROUGH */
		case LZMA_OK: /* Decompressor made some progress. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			state->member_in +=
			    avail_in - state->stream.avail_in;
			break;
		default:
			set_error(self, ret);
			return (ARCHIVE_FATAL);
		}