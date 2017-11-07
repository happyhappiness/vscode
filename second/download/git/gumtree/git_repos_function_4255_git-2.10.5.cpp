void bitmap_or_ewah(struct bitmap *self, struct ewah_bitmap *other)
{
	size_t original_size = self->word_alloc;
	size_t other_final = (other->bit_size / BITS_IN_EWORD) + 1;
	size_t i = 0;
	struct ewah_iterator it;
	eword_t word;

	if (self->word_alloc < other_final) {
		self->word_alloc = other_final;
		REALLOC_ARRAY(self->words, self->word_alloc);
		memset(self->words + original_size, 0x0,
			(self->word_alloc - original_size) * sizeof(eword_t));
	}

	ewah_iterator_init(&it, other);

	while (ewah_iterator_next(&word, &it))
		self->words[i++] |= word;
}