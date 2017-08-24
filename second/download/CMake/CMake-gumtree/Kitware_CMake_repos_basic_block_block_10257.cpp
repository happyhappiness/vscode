(state->stage) {
	case SELECT_STREAM:
		break;
	case READ_DEFAULT_STREAM:
	case READ_LEGACY_STREAM:
		/* Reading a lz4 stream already failed. */
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Invalid sequence.");
		return (ARCHIVE_FATAL);
	case READ_DEFAULT_BLOCK:
		ret = lz4_filter_read_default_stream(self, p);
		if (ret != 0 || state->stage != SELECT_STREAM)
			return ret;
		break;
	case READ_LEGACY_BLOCK:
		ret = lz4_filter_read_legacy_stream(self, p);
		if (ret != 0 || state->stage != SELECT_STREAM)
			return ret;
		break;
	default:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Program error.");
		return (ARCHIVE_FATAL);
		break;
	}