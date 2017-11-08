void ewah_not(struct ewah_bitmap *self)
{
	size_t pointer = 0;

	while (pointer < self->buffer_size) {
		eword_t *word = &self->buffer[pointer];
		size_t literals, k;

		rlw_xor_run_bit(word);
		++pointer;

		literals = rlw_get_literal_words(word);
		for (k = 0; k < literals; ++k) {
			self->buffer[pointer] = ~self->buffer[pointer];
			++pointer;
		}
	}
}