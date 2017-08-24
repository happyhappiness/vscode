{
		assert(*in_pos == in_size);
		ret = LZMA_OK;
		coder->mf.action = action;
		coder->mf.read_limit = coder->mf.write_pos;

	}