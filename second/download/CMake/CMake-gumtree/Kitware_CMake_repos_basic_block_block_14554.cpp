outsize = LZ4_compress_default(p, data->out + 4,
		    (int)length, (int)data->block_size)