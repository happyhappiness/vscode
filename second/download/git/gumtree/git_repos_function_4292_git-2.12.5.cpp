static void update_refstatus(int *ref_status, int nr, uint32_t *bitmap)
{
	unsigned int i;
	if (!ref_status)
		return;
	for (i = 0; i < nr; i++)
		if (bitmap[i / 32] & (1U << (i % 32)))
			ref_status[i]++;
}