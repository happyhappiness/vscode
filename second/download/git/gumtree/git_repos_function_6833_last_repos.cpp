void * nedpcalloc(nedpool *p, size_t no, size_t size) THROWSPEC
{
	size_t rsize=size*no;
	void *ret=0;
	threadcache *tc;
	int mymspace;
	GetThreadCache(&p, &tc, &mymspace, &rsize);
#if THREADCACHEMAX
	if(tc && rsize<=THREADCACHEMAX)
	{	/* Use the thread cache */
		if((ret=threadcache_malloc(p, tc, &rsize)))
			memset(ret, 0, rsize);
	}
#endif
	if(!ret)
	{	/* Use this thread's mspace */
	GETMSPACE(m, p, tc, mymspace, rsize,
		  ret=mspace_calloc(m, 1, rsize));
	}
	return ret;
}