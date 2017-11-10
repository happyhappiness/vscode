void * nedprealloc(nedpool *p, void *mem, size_t size) THROWSPEC
{
	void *ret=0;
	threadcache *tc;
	int mymspace;
	if(!mem) return nedpmalloc(p, size);
	GetThreadCache(&p, &tc, &mymspace, &size);
#if THREADCACHEMAX
	if(tc && size && size<=THREADCACHEMAX)
	{	/* Use the thread cache */
		size_t memsize=nedblksize(mem);
		assert(memsize);
		if((ret=threadcache_malloc(p, tc, &size)))
		{
			memcpy(ret, mem, memsize<size ? memsize : size);
			if(memsize<=THREADCACHEMAX)
				threadcache_free(p, tc, mymspace, mem, memsize);
			else
				mspace_free(0, mem);
		}
	}
#endif
	if(!ret)
	{	/* Reallocs always happen in the mspace they happened in, so skip
		locking the preferred mspace for this thread */
		ret=mspace_realloc(0, mem, size);
	}
	return ret;
}