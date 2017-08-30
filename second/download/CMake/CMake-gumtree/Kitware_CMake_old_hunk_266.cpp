		xar->lzstream.total_in = 0;

		xar->lzstream.total_out = 0;

		break;

#elif defined(HAVE_LZMADEC_H) && defined(HAVE_LIBLZMADEC)

	case LZMA:

		if (xar->lzstream_valid)

			lzmadec_end(&(xar->lzstream));

		r = lzmadec_init(&(xar->lzstream));

		if (r != LZMADEC_OK) {

			switch (r) {

			case LZMADEC_HEADER_ERROR:

				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "Internal error initializing "

				    "compression library: "

				    "invalid header");

				break;

			case LZMADEC_MEM_ERROR:

				archive_set_error(&a->archive,

				    ENOMEM,

				    "Internal error initializing "

				    "compression library: "

				    "out of memory");

				break;

			}

			return (ARCHIVE_FATAL);

		}

		xar->lzstream_valid = 1;

		xar->lzstream.total_in = 0;

		xar->lzstream.total_out = 0;

		break;

#endif

	/*

	 * Unsupported compression.

