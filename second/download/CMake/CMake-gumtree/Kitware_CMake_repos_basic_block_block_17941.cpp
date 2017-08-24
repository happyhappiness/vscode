{
		const lzma_ret ret = lzma_filter_flags_decode(
				&block->filters[i], allocator,
				in, &in_pos, in_size);
		if (ret != LZMA_OK) {
			free_properties(block, allocator);
			return ret;
		}
	}