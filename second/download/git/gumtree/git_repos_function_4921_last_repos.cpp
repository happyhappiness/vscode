void bitmap_reset(struct bitmap *bitmap)
{
	memset(bitmap->words, 0x0, bitmap->word_alloc * sizeof(eword_t));
}