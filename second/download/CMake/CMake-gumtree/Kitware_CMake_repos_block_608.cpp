{
		case BZ_RUN_OK:
			/* In non-finishing case, did compressor
			 * consume everything? */
			if (!finishing && data->stream.avail_in == 0)
				return (ARCHIVE_OK);
			break;
		case BZ_FINISH_OK:  /* Finishing: There's more work to do */
			break;
		case BZ_STREAM_END: /* Finishing: all done */
			/* Only occurs in finishing case */
			return (ARCHIVE_OK);
		default:
			/* Any other return value indicates an error */
			archive_set_error(f->archive,
			    ARCHIVE_ERRNO_PROGRAMMER,
			    "Bzip2 compression failed;"
			    " BZ2_bzCompress() returned %d",
			    ret);
			return (ARCHIVE_FATAL);
		}