	struct private_data *data = (struct private_data *)f->data;
	int outsize;

#define DICT_SIZE	(64 * 1024)
#ifdef HAVE_LZ4HC_H
	if (data->compression_level >= 3) {
		if (data->lz4_stream == NULL) {
#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
			data->lz4_stream = LZ4_createStreamHC();
			LZ4_resetStreamHC(data->lz4_stream, data->compression_level);
#else
			data->lz4_stream =
			    LZ4_createHC(data->in_buffer_allocated);
#endif
			if (data->lz4_stream == NULL) {
				archive_set_error(f->archive, ENOMEM,
				    "Can't allocate data for compression"
				    " buffer");
				return (ARCHIVE_FATAL);
			}
		}
		else
			LZ4_loadDictHC(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE);

#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
		outsize = LZ4_compress_HC_continue(
		    data->lz4_stream, p, data->out + 4, (int)length,
		    (int)data->block_size);
#else
		outsize = LZ4_compressHC2_limitedOutput_continue(
		    data->lz4_stream, p, data->out + 4, (int)length,
		    (int)data->block_size, data->compression_level);
#endif
	} else
#endif
	{
		if (data->lz4_stream == NULL) {
			data->lz4_stream = LZ4_createStream();
			if (data->lz4_stream == NULL) {
				archive_set_error(f->archive, ENOMEM,
				    "Can't allocate data for compression"
				    " buffer");
				return (ARCHIVE_FATAL);
			}
		}
		else
			LZ4_loadDict(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE);

#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
		outsize = LZ4_compress_fast_continue(
		    data->lz4_stream, p, data->out + 4, (int)length,
		    (int)data->block_size, 1);
#else
		outsize = LZ4_compress_limitedOutput_continue(
		    data->lz4_stream, p, data->out + 4, (int)length,
		    (int)data->block_size);
#endif
	}

	if (outsize) {
