void bitmap_clear(struct bitmap *self, size_t pos)
{
	size_t block = EWAH_BLOCK(pos);

	if (block < self->word_alloc)
		self->words[block] &= ~EWAH_MASK(pos);
}