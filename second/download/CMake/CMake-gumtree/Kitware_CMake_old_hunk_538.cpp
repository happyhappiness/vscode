	struct private_data *data = (struct private_data *)f->data;

	int outsize;



	if (data->compression_level < 3) {

		if (data->lz4_stream == NULL) {

			data->lz4_stream = LZ4_createStream();

			if (data->lz4_stream == NULL) {

				archive_set_error(f->archive, ENOMEM,

				    "Can't allocate data for compression"

				    " buffer");

				return (ARCHIVE_FATAL);

			}

		}

		outsize = LZ4_compress_limitedOutput_continue(

		    data->lz4_stream, p, data->out + 4, (int)length,

		    (int)data->block_size);

	} else {

		if (data->lz4_stream == NULL) {

			data->lz4_stream =

			    LZ4_createHC(data->in_buffer_allocated);

			if (data->lz4_stream == NULL) {

				archive_set_error(f->archive, ENOMEM,

				    "Can't allocate data for compression"

				    " buffer");

				return (ARCHIVE_FATAL);

			}

		}

		outsize = LZ4_compressHC2_limitedOutput_continue(

		    data->lz4_stream, p, data->out + 4, (int)length,

		    (int)data->block_size, data->compression_level);

	}



	if (outsize) {

