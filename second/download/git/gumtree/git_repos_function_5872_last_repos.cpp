static int outf(void *dummy, mmbuffer_t *ptr, int nbuf)
{
	int i;
	for (i = 0; i < nbuf; i++)
		if (write_in_full(1, ptr[i].ptr, ptr[i].size) != ptr[i].size)
			return -1;
	return 0;
}