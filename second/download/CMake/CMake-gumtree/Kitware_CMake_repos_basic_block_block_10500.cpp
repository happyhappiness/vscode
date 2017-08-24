{
	struct private_data *state;
	const unsigned char *h;
	lzma_filter filters[2];
	unsigned char props[5];
	ssize_t avail_in;
	uint32_t dicsize;
	int log2dic, ret;

	state = (struct private_data *)self->data;
	h = __archive_read_filter_ahead(self->upstream, 6, &avail_in);
	if (h == NULL)
		return (ARCHIVE_FATAL);

	/* Get a version number. */
	state->lzip_ver = h[4];

	/*
	 * Setup lzma property.
	 */
	props[0] = 0x5d;

	/* Get dictionary size. */
	log2dic = h[5] & 0x1f;
	if (log2dic < 12 || log2dic > 27)
		return (ARCHIVE_FATAL);
	dicsize = 1U << log2dic;
	if (log2dic > 12)
		dicsize -= (dicsize / 16) * (h[5] >> 5);
	archive_le32enc(props+1, dicsize);

	/* Consume lzip header. */
	__archive_read_filter_consume(self->upstream, 6);
	state->member_in = 6;

	filters[0].id = LZMA_FILTER_LZMA1;
	filters[0].options = NULL;
	filters[1].id = LZMA_VLI_UNKNOWN;
	filters[1].options = NULL;

	ret = lzma_properties_decode(&filters[0], NULL, props, sizeof(props));
	if (ret != LZMA_OK) {
		set_error(self, ret);
		return (ARCHIVE_FATAL);
	}
	ret = lzma_raw_decoder(&(state->stream), filters);
	free(filters[0].options);
	if (ret != LZMA_OK) {
		set_error(self, ret);
		return (ARCHIVE_FATAL);
	}
	return (ARCHIVE_OK);
}