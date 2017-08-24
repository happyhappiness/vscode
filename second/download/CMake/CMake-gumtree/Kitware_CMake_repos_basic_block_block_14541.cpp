(data->compression_level >= 3)
#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
			LZ4_freeStreamHC(data->lz4_stream)