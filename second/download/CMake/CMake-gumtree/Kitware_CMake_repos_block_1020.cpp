{
	case LZMA_OK:
		/* Non-finishing case */
		return (ARCHIVE_OK);
	case LZMA_STREAM_END:
		/* This return can only occur in finishing case. */
		return (ARCHIVE_EOF);
	case LZMA_MEMLIMIT_ERROR:
		archive_set_error(a, ENOMEM,
		    "lzma compression error:"
		    " %ju MiB would have been needed",
		    (uintmax_t)((lzma_memusage(strm) + 1024 * 1024 -1)
			/ (1024 * 1024)));
		return (ARCHIVE_FATAL);
	default:
		/* Any other return value indicates an error */
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "lzma compression failed:"
		    " lzma_code() call returned status %d", r);
		return (ARCHIVE_FATAL);
	}