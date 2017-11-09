size_t bitmap_popcount(struct bitmap *self)
{
	size_t i, count = 0;

	for (i = 0; i < self->word_alloc; ++i)
		count += ewah_bit_popcount64(self->words[i]);

	return count;
}