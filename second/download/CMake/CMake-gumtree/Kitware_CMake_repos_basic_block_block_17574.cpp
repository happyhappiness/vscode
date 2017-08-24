{
		memset(&mt_options, 0, sizeof(mt_options));
		mt_options.threads = threads;
		mt_options.timeout = 300;
		mt_options.filters = lzmafilters;
		mt_options.check = LZMA_CHECK_CRC64;
		r = lzma_stream_encoder_mt(strm, &mt_options);
	}