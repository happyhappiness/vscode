static inline int item_watched(int i)
{
	assert (i >= 0);
	assert (i < ((STATIC_ARRAY_SIZE (watch_items) + 1) * 32));
	return watch_items[i / 32] & FLAG (i);
}