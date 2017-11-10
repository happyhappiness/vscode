static int show_outf(void *priv_, mmbuffer_t *mb, int nbuf)
{
	int i;
	for (i = 0; i < nbuf; i++)
		printf("%.*s", (int) mb[i].size, mb[i].ptr);
	return 0;
}