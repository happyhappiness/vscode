(f->code == ARCHIVE_FILTER_LZMA) {
		ret = lzma_alone_encoder(&(data->stream), &data->lzma_opt);
	}