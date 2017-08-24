{
		size_t in_pos = 0;
		ret = raw_encoder.code(raw_encoder.coder, allocator,
				in, &in_pos, in_size, out, out_pos, out_size,
				LZMA_FINISH);
	}