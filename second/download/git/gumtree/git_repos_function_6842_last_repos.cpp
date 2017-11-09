void **nedpindependent_calloc(nedpool *p, size_t elemsno, size_t elemsize, void **chunks) THROWSPEC
{
	void **ret;
	threadcache *tc;
	int mymspace;
	GetThreadCache(&p, &tc, &mymspace, &elemsize);
    GETMSPACE(m, p, tc, mymspace, elemsno*elemsize,
	      ret=mspace_independent_calloc(m, elemsno, elemsize, chunks));
	return ret;
}