int ewah_serialize_to(struct ewah_bitmap *self,
		      int (*write_fun)(void *, const void *, size_t),
		      void *data)
{
	size_t i;
	eword_t dump[2048];
	const size_t words_per_dump = sizeof(dump) / sizeof(eword_t);
	uint32_t bitsize, word_count, rlw_pos;

	const eword_t *buffer;
	size_t words_left;

	/* 32 bit -- bit size for the map */
	bitsize =  htonl((uint32_t)self->bit_size);
	if (write_fun(data, &bitsize, 4) != 4)
		return -1;

	/** 32 bit -- number of compressed 64-bit words */
	word_count =  htonl((uint32_t)self->buffer_size);
	if (write_fun(data, &word_count, 4) != 4)
		return -1;

	/** 64 bit x N -- compressed words */
	buffer = self->buffer;
	words_left = self->buffer_size;

	while (words_left >= words_per_dump) {
		for (i = 0; i < words_per_dump; ++i, ++buffer)
			dump[i] = htonll(*buffer);

		if (write_fun(data, dump, sizeof(dump)) != sizeof(dump))
			return -1;

		words_left -= words_per_dump;
	}

	if (words_left) {
		for (i = 0; i < words_left; ++i, ++buffer)
			dump[i] = htonll(*buffer);

		if (write_fun(data, dump, words_left * 8) != words_left * 8)
			return -1;
	}

	/** 32 bit -- position for the RLW */
	rlw_pos = (uint8_t*)self->rlw - (uint8_t *)self->buffer;
	rlw_pos = htonl(rlw_pos / sizeof(eword_t));

	if (write_fun(data, &rlw_pos, 4) != 4)
		return -1;

	return (3 * 4) + (self->buffer_size * 8);
}