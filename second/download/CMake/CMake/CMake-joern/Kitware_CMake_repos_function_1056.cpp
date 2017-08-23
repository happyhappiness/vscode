static int
drive_compressor_dependence(struct archive_write_filter *f, const char *p,
    size_t length)
{
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
		/* The buffer is compressed. */
		archive_le32enc(data->out, outsize);
		data->out += 4;
	} else {
		/* The buffer is not compressed. The compressed size was
		 * bigger than its uncompressed size. */
		archive_le32enc(data->out, length | 0x80000000);
		data->out += 4;
		memcpy(data->out, p, length);
		outsize = length;
	}
	data->out += outsize;
	if (data->block_checksum) {
		unsigned int checksum =
		    __archive_xxhash.XXH32(data->out - outsize, outsize, 0);
		archive_le32enc(data->out, checksum);
		data->out += 4;
	}

	if (length == data->block_size) {
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
	return (ARCHIVE_OK);
}