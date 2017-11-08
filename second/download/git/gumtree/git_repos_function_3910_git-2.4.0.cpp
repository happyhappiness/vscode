struct ewah_bitmap *ewah_pool_new(void)
{
	if (bitmap_pool_size)
		return bitmap_pool[--bitmap_pool_size];

	return ewah_new();
}