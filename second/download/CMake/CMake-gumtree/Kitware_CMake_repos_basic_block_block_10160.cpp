ret = BZ2_bzDecompressInit(&(state->stream),
					   0 /* library verbosity */,
					   1 /* do use low-mem algo */)