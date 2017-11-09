void **nedpindependent_comalloc(nedpool *p, size_t elems, size_t *sizes, void **chunks) THROWSPEC
{
	void **ret;
	threadcache *tc;
	int mymspace;
	size_t i, *adjustedsizes=(size_t *) alloca(elems*sizeof(size_t));
	if(!adjustedsizes) return 0;
	for(i=0; i<elems; i++)
		adjustedsizes[i]=sizes[i]<sizeof(threadcacheblk) ? sizeof(threadcacheblk) : sizes[i];
	GetThreadCache(&p, &tc, &mymspace, 0);
	GETMSPACE(m, p, tc, mymspace, 0,
	      ret=mspace_independent_comalloc(m, elems, adjustedsizes, chunks));
	return ret;
}