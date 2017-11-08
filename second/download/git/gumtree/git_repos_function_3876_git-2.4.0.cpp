int bitmap_get(struct bitmap *self, size_t pos)
{
	size_t block = BLOCK(pos);
	return block < self->word_alloc &&
		(self->words[block] & MASK(pos)) != 0;
}