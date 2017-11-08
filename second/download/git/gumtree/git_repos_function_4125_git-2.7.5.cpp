size_t ewah_add_empty_words(struct ewah_bitmap *self, int v, size_t number)
{
	if (number == 0)
		return 0;

	self->bit_size += number * BITS_IN_EWORD;
	return add_empty_words(self, v, number);
}