void ewah_set(struct ewah_bitmap *self, size_t i)
{
	const size_t dist =
		(i + BITS_IN_WORD) / BITS_IN_WORD -
		(self->bit_size + BITS_IN_WORD - 1) / BITS_IN_WORD;

	assert(i >= self->bit_size);

	self->bit_size = i + 1;

	if (dist > 0) {
		if (dist > 1)
			add_empty_words(self, 0, dist - 1);

		add_literal(self, (eword_t)1 << (i % BITS_IN_WORD));
		return;
	}

	if (rlw_get_literal_words(self->rlw) == 0) {
		rlw_set_running_len(self->rlw,
			rlw_get_running_len(self->rlw) - 1);
		add_literal(self, (eword_t)1 << (i % BITS_IN_WORD));
		return;
	}

	self->buffer[self->buffer_size - 1] |=
		((eword_t)1 << (i % BITS_IN_WORD));

	/* check if we just completed a stream of 1s */
	if (self->buffer[self->buffer_size - 1] == (eword_t)(~0)) {
		self->buffer[--self->buffer_size] = 0;
		rlw_set_literal_words(self->rlw,
			rlw_get_literal_words(self->rlw) - 1);
		add_empty_word(self, 1);
	}
}