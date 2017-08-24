{
			memset(&mt_options, 0, sizeof(mt_options));
			mt_options.threads = data->threads;
			mt_options.timeout = 300;
			mt_options.filters = data->lzmafilters;
			mt_options.check = LZMA_CHECK_CRC64;
			ret = lzma_stream_encoder_mt(&(data->stream),
			    &mt_options);
		}