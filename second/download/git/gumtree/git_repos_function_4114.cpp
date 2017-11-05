void bitmap_each_bit(struct bitmap *self, ewah_callback callback, void *data)
{
	size_t pos = 0, i;

	for (i = 0; i < self->word_alloc; ++i) {
		eword_t word = self->words[i];
		uint32_t offset;

		if (word == (eword_t)~0) {
			for (offset = 0; offset < BITS_IN_EWORD; ++offset)
				callback(pos++, data);
		} else {
			for (offset = 0; offset < BITS_IN_EWORD; ++offset) {
				if ((word >> offset) == 0)
					break;

				offset += ewah_bit_ctz64(word >> offset);
				callback(pos + offset, data);
			}
			pos += BITS_IN_EWORD;
		}
	}
}