void bitmap_free(struct bitmap *bitmap)
{
	if (bitmap == NULL)
		return;

	free(bitmap->words);
	free(bitmap);
}