static NOINLINE threadcache *AllocCache(nedpool *p) THROWSPEC
{
	threadcache *tc=0;
	int n, end;
	ACQUIRE_LOCK(&p->mutex);
	for(n=0; n<THREADCACHEMAXCACHES && p->caches[n]; n++);
	if(THREADCACHEMAXCACHES==n)
	{	/* List exhausted, so disable for this thread */
		RELEASE_LOCK(&p->mutex);
		return 0;
	}
	tc=p->caches[n]=(threadcache *) mspace_calloc(p->m[0], 1, sizeof(threadcache));
	if(!tc)
	{
		RELEASE_LOCK(&p->mutex);
		return 0;
	}
#ifdef FULLSANITYCHECKS
	tc->magic1=*(unsigned int *)"NEDMALC1";
	tc->magic2=*(unsigned int *)"NEDMALC2";
#endif
	tc->threadid=(long)(size_t)CURRENT_THREAD;
	for(end=0; p->m[end]; end++);
	tc->mymspace=tc->threadid % end;
	RELEASE_LOCK(&p->mutex);
	if(TLSSET(p->mycache, (void *)(size_t)(n+1))) abort();
	return tc;
}