struct ewah_bitmap *bitmap_to_ewah(struct bitmap *bitmap)
{
	struct ewah_bitmap *ewah = ewah_new();
	size_t i, running_empty_words = 0;
	eword_t last_word = 0;

	for (i = 0; i < bitmap->word_alloc; ++i) {
		if (bitmap->words[i] == 0) {
			running_empty_words++;
			continue;
		}

		if (last_word != 0)
			ewah_add(ewah, last_word);

		if (running_empty_words > 0) {
			ewah_add_empty_words(ewah, 0, running_empty_words);
			running_empty_words = 0;
		}

		last_word = bitmap->words[i];
	}

	ewah_add(ewah, last_word);
	return ewah;
}