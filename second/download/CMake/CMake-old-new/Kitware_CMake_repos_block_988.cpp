{
	case LZMA_OK:
		lastrm->real_stream = strm;
		lastrm->valid = 1;
		lastrm->code = compression_code_lzma;
		lastrm->end = compression_end_lzma;
		r = ARCHIVE_OK;
		break;
	case LZMA_MEM_ERROR:
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ENOMEM,
		    "Internal error initializing compression library: "
		    "Cannot allocate memory");
		r =  ARCHIVE_FATAL;
		break;
        default:
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "It's a bug in liblzma");
		r =  ARCHIVE_FATAL;
		break;
	}