static inline void watchlist_remove (uint32_t *wl, int item)
{
	assert (item >= 0);
	assert (item < WL_LEN * 32);
	wl[item / 32] &= ~FLAG (item);
}