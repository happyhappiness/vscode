void * nedpmalloc(nedpool *p, size_t size) THROWSPEC
{
	void *ret=0;
	threadcache *tc;
	int mymspace;
	GetThreadCache(&p, &tc, &mymspace, &size);
#if THREADCACHEMAX
	if(tc && size<=THREADCACHEMAX)
	{	/* Use the thread cache */
		ret=threadcache_malloc(p, tc, &size);
	}
#endif
	if(!ret)
	{	/* Use this thread's mspace */
	GETMSPACE(m, p, tc, mymspace, size,
		  ret=mspace_malloc(m, size));
	}
	return ret;
}