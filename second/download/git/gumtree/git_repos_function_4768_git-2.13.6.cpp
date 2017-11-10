struct bitmap *bitmap_new(void)
{
	struct bitmap *bitmap = xmalloc(sizeof(struct bitmap));
	bitmap->words = xcalloc(32, sizeof(eword_t));
	bitmap->word_alloc = 32;
	return bitmap;
}