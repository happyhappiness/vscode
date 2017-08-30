		}

		return (ARCHIVE_OK);

	}

	if (strcmp(key, "threads") == 0) {

		if (value == NULL)

			return (ARCHIVE_FAILED);

		xar->opt_threads = (int)strtoul(value, NULL, 10);

		if (xar->opt_threads == 0 && errno != 0) {

			xar->opt_threads = 1;

			archive_set_error(&(a->archive),

			    ARCHIVE_ERRNO_MISC,

			    "Illegal value `%s'",

			    value);

			return (ARCHIVE_FAILED);

		}

		if (xar->opt_threads == 0) {

#ifdef HAVE_LZMA_STREAM_ENCODER_MT

			xar->opt_threads = lzma_cputhreads();

#else

			xar->opt_threads = 1;

#endif

		}

	}



	/* Note: The "warn" return is just to inform the options

	 * supervisor that we didn't handle it.  It will generate

