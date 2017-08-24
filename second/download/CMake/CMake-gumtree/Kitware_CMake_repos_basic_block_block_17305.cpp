(xar->opt_threads == 0) {
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
			xar->opt_threads = lzma_cputhreads();
#else
			xar->opt_threads = 1;
#endif
		}