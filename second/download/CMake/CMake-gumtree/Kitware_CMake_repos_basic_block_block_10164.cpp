{
		switch (BZ2_bzDecompressEnd(&state->stream)) {
		case BZ_OK:
			break;
		default:
			archive_set_error(&self->archive->archive,
					  ARCHIVE_ERRNO_MISC,
					  "Failed to clean up decompressor");
			ret = ARCHIVE_FATAL;
		}
		state->valid = 0;
	}