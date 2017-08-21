		*used = avail_in - xar->lzstream.avail_in;
		*outbytes = avail_out - xar->lzstream.avail_out;
		break;
#elif defined(HAVE_LZMADEC_H) && defined(HAVE_LIBLZMADEC)
	case LZMA:
		xar->lzstream.next_in = (unsigned char *)(uintptr_t)b;
		xar->lzstream.avail_in = avail_in;
		xar->lzstream.next_out = (unsigned char *)outbuff;
		xar->lzstream.avail_out = avail_out;
		r = lzmadec_decode(&(xar->lzstream), 0);
		switch (r) {
		case LZMADEC_STREAM_END: /* Found end of stream. */
			switch (lzmadec_end(&(xar->lzstream))) {
			case LZMADEC_OK:
				break;
			default:
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Failed to clean up lzmadec decompressor");
				return (ARCHIVE_FATAL);
			}
			xar->lzstream_valid = 0;
			/* FALLTHROUGH */
		case LZMADEC_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "lzmadec decompression failed(%d)",
			    r);
			return (ARCHIVE_FATAL);
		}
		*used = avail_in - xar->lzstream.avail_in;
		*outbytes = avail_out - xar->lzstream.avail_out;
		break;
#endif
#if !defined(HAVE_BZLIB_H) || !defined(BZ_CONFIG_ERROR)
	case BZIP2:
#endif
#if !defined(HAVE_LZMA_H) || !defined(HAVE_LIBLZMA)
#if !defined(HAVE_LZMADEC_H) || !defined(HAVE_LIBLZMADEC)
	case LZMA:
#endif
	case XZ:
#endif
	case NONE:
