(data->threads == 0) {
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
			data->threads = lzma_cputhreads();
#else
			data->threads = 1;
#endif
		}