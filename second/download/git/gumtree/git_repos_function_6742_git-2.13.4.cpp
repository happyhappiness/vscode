void * nedpmemalign(nedpool *p, size_t alignment, size_t bytes) THROWSPEC
{
	void *ret;
	threadcache *tc;
	int mymspace;
	GetThreadCache(&p, &tc, &mymspace, &bytes);
	{	/* Use this thread's mspace */
	GETMSPACE(m, p, tc, mymspace, bytes,
		  ret=mspace_memalign(m, alignment, bytes));
	}
	return ret;
}