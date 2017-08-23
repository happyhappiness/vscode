static int
archive_compressor_xz_open(struct archive_write_filter *f)
{
	struct private_data *data = f->data;
	int ret;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != ARCHIVE_OK)
		return (ret);

	if (data->compressed == NULL) {
		size_t bs = 65536, bpb;
		if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
			/* Buffer size should be a multiple number of the of bytes
			 * per block for performance. */
			bpb = archive_write_get_bytes_per_block(f->archive);
			if (bpb > bs)
				bs = bpb;
			else if (bpb != 0)
				bs -= bs % bpb;
		}
		data->compressed_buffer_size = bs;
		data->compressed
		    = (unsigned char *)malloc(data->compressed_buffer_size);
		if (data->compressed == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
	}

	f->write = archive_compressor_xz_write;

	/* Initialize compression library. */
	if (f->code == ARCHIVE_FILTER_LZIP) {
		const struct option_value *val =
		    &option_values[data->compression_level];

		data->lzma_opt.dict_size = val->dict_size;
		data->lzma_opt.preset_dict = NULL;
		data->lzma_opt.preset_dict_size = 0;
		data->lzma_opt.lc = LZMA_LC_DEFAULT;
		data->lzma_opt.lp = LZMA_LP_DEFAULT;
		data->lzma_opt.pb = LZMA_PB_DEFAULT;
		data->lzma_opt.mode =
		    data->compression_level<= 2? LZMA_MODE_FAST:LZMA_MODE_NORMAL;
		data->lzma_opt.nice_len = val->nice_len;
		data->lzma_opt.mf = val->mf;
		data->lzma_opt.depth = 0;
		data->lzmafilters[0].id = LZMA_FILTER_LZMA1;
		data->lzmafilters[0].options = &data->lzma_opt;
		data->lzmafilters[1].id = LZMA_VLI_UNKNOWN;/* Terminate */
	} else {
		if (lzma_lzma_preset(&data->lzma_opt, data->compression_level)) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "Internal error initializing compression library");
		}
		data->lzmafilters[0].id = LZMA_FILTER_LZMA2;
		data->lzmafilters[0].options = &data->lzma_opt;
		data->lzmafilters[1].id = LZMA_VLI_UNKNOWN;/* Terminate */
	}
	ret = archive_compressor_xz_init_stream(f, data);
	if (ret == LZMA_OK) {
		f->data = data;
		return (0);
	}
	return (ARCHIVE_FATAL);
}