int ewah_deserialize(struct ewah_bitmap *self, int fd)
{
	size_t i;
	eword_t dump[2048];
	const size_t words_per_dump = sizeof(dump) / sizeof(eword_t);
	uint32_t bitsize, word_count, rlw_pos;

	eword_t *buffer = NULL;
	size_t words_left;

	ewah_clear(self);

	/* 32 bit -- bit size for the map */
	if (read(fd, &bitsize, 4) != 4)
		return -1;

	self->bit_size = (size_t)ntohl(bitsize);

	/** 32 bit -- number of compressed 64-bit words */
	if (read(fd, &word_count, 4) != 4)
		return -1;

	self->buffer_size = self->alloc_size = (size_t)ntohl(word_count);
	REALLOC_ARRAY(self->buffer, self->alloc_size);

	/** 64 bit x N -- compressed words */
	buffer = self->buffer;
	words_left = self->buffer_size;

	while (words_left >= words_per_dump) {
		if (read(fd, dump, sizeof(dump)) != sizeof(dump))
			return -1;

		for (i = 0; i < words_per_dump; ++i, ++buffer)
			*buffer = ntohll(dump[i]);

		words_left -= words_per_dump;
	}

	if (words_left) {
		if (read(fd, dump, words_left * 8) != words_left * 8)
			return -1;

		for (i = 0; i < words_left; ++i, ++buffer)
			*buffer = ntohll(dump[i]);
	}

	/** 32 bit -- position for the RLW */
	if (read(fd, &rlw_pos, 4) != 4)
		return -1;

	self->rlw = self->buffer + ntohl(rlw_pos);
	return 0;
}