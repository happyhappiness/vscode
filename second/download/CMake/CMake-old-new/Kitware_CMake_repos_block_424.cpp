{
	case BZ_RUN_OK:     /* Non-finishing */
	case BZ_FINISH_OK:  /* Finishing: There's more work to do */
		return (ARCHIVE_OK);
	case BZ_STREAM_END: /* Finishing: all done */
		/* Only occurs in finishing case */
		return (ARCHIVE_EOF);
	default:
		/* Any other return value indicates an error */
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Bzip2 compression failed:"
		    " BZ2_bzCompress() call returned status %d", r);
		return (ARCHIVE_FATAL);
	}