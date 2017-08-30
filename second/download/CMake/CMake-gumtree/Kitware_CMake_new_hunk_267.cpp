		*used = avail_in - xar->lzstream.avail_in;
		*outbytes = avail_out - xar->lzstream.avail_out;
		break;
#endif
#if !defined(HAVE_BZLIB_H) || !defined(BZ_CONFIG_ERROR)
	case BZIP2:
#endif
#if !defined(HAVE_LZMA_H) || !defined(HAVE_LIBLZMA)
	case LZMA:
	case XZ:
#endif
	case NONE:
