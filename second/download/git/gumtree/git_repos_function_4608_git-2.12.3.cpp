struct bitmap *ewah_to_bitmap(struct ewah_bitmap *ewah)
{
	struct bitmap *bitmap = bitmap_new();
	struct ewah_iterator it;
	eword_t blowup;
	size_t i = 0;

	ewah_iterator_init(&it, ewah);

	while (ewah_iterator_next(&blowup, &it)) {
		ALLOC_GROW(bitmap->words, i + 1, bitmap->word_alloc);
		bitmap->words[i++] = blowup;
	}

	bitmap->word_alloc = i;
	return bitmap;
}