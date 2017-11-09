size_t ewah_add(struct ewah_bitmap *self, eword_t word)
{
	self->bit_size += BITS_IN_EWORD;

	if (word == 0)
		return add_empty_word(self, 0);

	if (word == (eword_t)(~0))
		return add_empty_word(self, 1);

	return add_literal(self, word);
}