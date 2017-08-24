(a->backward_size != LZMA_VLI_UNKNOWN
			&& b->backward_size != LZMA_VLI_UNKNOWN) {
		if (!is_backward_size_valid(a) || !is_backward_size_valid(b))
			return LZMA_PROG_ERROR;

		if (a->backward_size != b->backward_size)
			return LZMA_DATA_ERROR;
	}