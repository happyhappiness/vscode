void neddisablethreadcache(nedpool *p) THROWSPEC
{
	int mycache;
	if(!p)
	{
		p=&syspool;
		if(!syspool.threads) InitPool(&syspool, 0, -1);
	}
	mycache=(int)(size_t) TLSGET(p->mycache);
	if(!mycache)
	{	/* Set to mspace 0 */
		if(TLSSET(p->mycache, (void *)-1)) abort();
	}
	else if(mycache>0)
	{	/* Set to last used mspace */
		threadcache *tc=p->caches[mycache-1];
#if defined(DEBUG)
		printf("Threadcache utilisation: %lf%% in cache with %lf%% lost to other threads\n",
			100.0*tc->successes/tc->mallocs, 100.0*((double) tc->mallocs-tc->frees)/tc->mallocs);
#endif
		if(TLSSET(p->mycache, (void *)(size_t)(-tc->mymspace))) abort();
		tc->frees++;
		RemoveCacheEntries(p, tc, 0);
		assert(!tc->freeInCache);
		tc->mymspace=-1;
		tc->threadid=0;
		mspace_free(0, p->caches[mycache-1]);
		p->caches[mycache-1]=0;
	}
}