{
	case LZMADEC_HEADER_ERROR:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "invalid header");
		break;
	case LZMADEC_MEM_ERROR:
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Internal error initializing compression library: "
		    "out of memory");
		break;
	}