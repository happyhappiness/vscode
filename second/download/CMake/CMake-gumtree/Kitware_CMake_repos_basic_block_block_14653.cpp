(ret) {
	case LZMA_MEM_ERROR:
		archive_set_error(f->archive, ENOMEM,
		    "Internal error initializing compression library: "
		    "Cannot allocate memory");
		break;
	default:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "It's a bug in liblzma");
		break;
	}