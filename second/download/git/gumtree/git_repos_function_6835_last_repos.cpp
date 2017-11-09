void   nedpfree(nedpool *p, void *mem) THROWSPEC
{	/* Frees always happen in the mspace they happened in, so skip
	locking the preferred mspace for this thread */
	threadcache *tc;
	int mymspace;
	size_t memsize;
	assert(mem);
	GetThreadCache(&p, &tc, &mymspace, 0);
#if THREADCACHEMAX
	memsize=nedblksize(mem);
	assert(memsize);
	if(mem && tc && memsize<=(THREADCACHEMAX+CHUNK_OVERHEAD))
		threadcache_free(p, tc, mymspace, mem, memsize);
	else
#endif
		mspace_free(0, mem);
}