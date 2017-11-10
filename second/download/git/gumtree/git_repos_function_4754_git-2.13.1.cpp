int bitmap_get(struct bitmap *self, size_t pos)
{
	size_t block = EWAH_BLOCK(pos);
	return block < self->word_alloc &&
		(self->words[block] & EWAH_MASK(pos)) != 0;
}