static inline void watchlist_set (uint32_t *wl, uint32_t val)
{
	int i;
	for (i = 0; i < WL_LEN; i++)
		wl[i] = val;
}