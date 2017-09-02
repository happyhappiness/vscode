static int
archive_compressor_xz_init_stream(struct archive_write_filter *f,
    struct private_data *data)
{
	static const lzma_stream lzma_stream_init_data = LZMA_STREAM_INIT;
	int ret;
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
	lzma_mt mt_options;
#endif

	data->stream = lzma_stream_init_data;
	data->stream.next_out = data->compressed;
	data->stream.avail_out = data->compressed_buffer_size;
	if (f->code == ARCHIVE_FILTER_XZ) {
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
		if (data->threads != 1) {
			bzero(&mt_options, sizeof(mt_options));
			mt_options.threads = data->threads;
			mt_options.timeout = 300;
			mt_options.filters = data->lzmafilters;
			mt_options.check = LZMA_CHECK_CRC64;
			ret = lzma_stream_encoder_mt(&(data->stream),
			    &mt_options);
		} else
#endif
			ret = lzma_stream_encoder(&(data->stream),
			    data->lzmafilters, LZMA_CHECK_CRC64);
	} else if (f->code == ARCHIVE_FILTER_LZMA) {
		ret = lzma_alone_encoder(&(data->stream), &data->lzma_opt);
	} else {	/* ARCHIVE_FILTER_LZIP */
		int dict_size = data->lzma_opt.dict_size;
		int ds, log2dic, wedges;

		/* Calculate a coded dictionary size */
		if (dict_size < (1 << 12) || dict_size > (1 << 27)) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "Unacceptable dictionary size for lzip: %d",
			    dict_size);
			return (ARCHIVE_FATAL);
		}
		for (log2dic = 27; log2dic >= 12; log2dic--) {
			if (dict_size & (1 << log2dic))
				break;
		}
		if (dict_size > (1 << log2dic)) {
			log2dic++;
			wedges =
			    ((1 << log2dic) - dict_size) / (1 << (log2dic - 4));
		} else
			wedges = 0;
		ds = ((wedges << 5) & 0xe0) | (log2dic & 0x1f);

		data->crc32 = 0;
		/* Make a header */
		data->compressed[0] = 0x4C;
		data->compressed[1] = 0x5A;
		data->compressed[2] = 0x49;
		data->compressed[3] = 0x50;
		data->compressed[4] = 1;/* Version */
		data->compressed[5] = (unsigned char)ds;
		data->stream.next_out += 6;
		data->stream.avail_out -= 6;

		ret = lzma_raw_encoder(&(data->stream), data->lzmafilters);
	}
	if (ret == LZMA_OK)
		return (ARCHIVE_OK);

	switch (ret) {
	case LZMA_MEM_ERROR:
		archive_set_error(f->archive, ENOMEM,
		    "Internal error initializing compression library: "
		    "Cannot allocate memory");
		break;
	default:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "It's a bug in liblzma");
		break;
	}
	return (ARCHIVE_FATAL);
}