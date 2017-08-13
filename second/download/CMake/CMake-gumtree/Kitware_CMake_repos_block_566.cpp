{
		case BZ_STREAM_END: /* Found end of stream. */
			switch (BZ2_bzDecompressEnd(&(state->stream))) {
			case BZ_OK:
				break;
			default:
				archive_set_error(&(self->archive->archive),
					  ARCHIVE_ERRNO_MISC,
					  "Failed to clean up decompressor");
				return (ARCHIVE_FATAL);
			}
			state->valid = 0;
			/* FALLTHROUGH */
		case BZ_OK: /* Decompressor made some progress. */
			/* If we filled our buffer, update stats and return. */
			if (state->stream.avail_out == 0) {
				*p = state->out_block;
				decompressed = state->stream.next_out
				    - state->out_block;
				return (decompressed);
			}
			break;
		default: /* Return an error. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC, "bzip decompression failed");
			return (ARCHIVE_FATAL);
		}