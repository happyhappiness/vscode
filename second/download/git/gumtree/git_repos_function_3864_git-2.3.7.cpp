struct bitmap *bitmap_new(void)
{
	struct bitmap *bitmap = ewah_malloc(sizeof(struct bitmap));
	bitmap->words = ewah_calloc(32, sizeof(eword_t));
	bitmap->word_alloc = 32;
	return bitmap;
}