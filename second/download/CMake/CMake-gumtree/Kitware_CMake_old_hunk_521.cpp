{
	static const lzma_stream lzma_stream_init_data = LZMA_STREAM_INIT;
	int ret;

	data->stream = lzma_stream_init_data;
	data->stream.next_out = data->compressed;
	data->stream.avail_out = data->compressed_buffer_size;
	if (f->code == ARCHIVE_FILTER_XZ)
		ret = lzma_stream_encoder(&(data->stream),
		    data->lzmafilters, LZMA_CHECK_CRC64);
	else if (f->code == ARCHIVE_FILTER_LZMA)
		ret = lzma_alone_encoder(&(data->stream), &data->lzma_opt);
	else {	/* ARCHIVE_FILTER_LZIP */
		int dict_size = data->lzma_opt.dict_size;
		int ds, log2dic, wedges;

		/* Calculate a coded dictionary size */
		if (dict_size < (1 << 12) || dict_size > (1 << 27)) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "Unacceptable dictionary dize for lzip: %d",
			    dict_size);
			return (ARCHIVE_FATAL);
		}
