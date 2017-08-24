(length == data->block_size) {
#ifdef HAVE_LZ4HC_H
		if (data->compression_level >= 3) {
#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
			LZ4_saveDictHC(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE);
#else
			LZ4_slideInputBufferHC(data->lz4_stream);
#endif
			data->in_buffer = data->in_buffer_allocated + DICT_SIZE;
		}
		else
#endif
			LZ4_saveDict(data->lz4_stream,
			    data->in_buffer_allocated, DICT_SIZE);
#undef DICT_SIZE
	}