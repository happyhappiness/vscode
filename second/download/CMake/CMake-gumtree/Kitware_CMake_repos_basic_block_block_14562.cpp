(data->lz4_stream == NULL) {
			data->lz4_stream = LZ4_createStream();
			if (data->lz4_stream == NULL) {
				archive_set_error(f->archive, ENOMEM,
				    "Can't allocate data for compression"
				    " buffer");
				return (ARCHIVE_FATAL);
			}
		}
		else
			LZ4_loadDict(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE)