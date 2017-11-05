void bitmap_set(struct bitmap *self, size_t pos)
{
	size_t block = EWAH_BLOCK(pos);

	if (block >= self->word_alloc) {
		size_t old_size = self->word_alloc;
		self->word_alloc = block * 2;
		self->words = ewah_realloc(self->words,
			self->word_alloc * sizeof(eword_t));

		memset(self->words + old_size, 0x0,
			(self->word_alloc - old_size) * sizeof(eword_t));
	}

	self->words[block] |= EWAH_MASK(pos);
}