static void make_mask(char *mask, int plen, int addrlen)
{
	int w, b;

	w = plen >> 3;
	b = plen & 0x7;

	if (w)
		memset(mask, 0xff, w);
	if (w < addrlen)
		mask[w] = 0xff & (0xff<<(8-b));
	if (w+1 < addrlen)
		memset(mask+w+1, 0, addrlen-w-1);

	return;
}