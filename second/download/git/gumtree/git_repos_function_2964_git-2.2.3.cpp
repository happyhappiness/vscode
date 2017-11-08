static int common_outf(void *priv_, mmbuffer_t *mb, int nbuf)
{
	int i;
	mmfile_t *dst = priv_;

	for (i = 0; i < nbuf; i++) {
		memcpy(dst->ptr + dst->size, mb[i].ptr, mb[i].size);
		dst->size += mb[i].size;
	}
	return 0;
}