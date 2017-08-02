{
	case LZO_E_OK:
		if (out_size == state->uncompressed_size)
			break;
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Corrupted data");
		return (ARCHIVE_FATAL);
	case LZO_E_OUT_OF_MEMORY:
		archive_set_error(&self->archive->archive, ENOMEM,
		    "lzop decompression failed: out of memory");
		return (ARCHIVE_FATAL);
	default:
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "lzop decompression failed: %d", r);
		return (ARCHIVE_FATAL);
	}