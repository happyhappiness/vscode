static void DestroyCaches(nedpool *p) THROWSPEC
{
	if(p->caches)
	{
		threadcache *tc;
		int n;
		for(n=0; n<THREADCACHEMAXCACHES; n++)
		{
			if((tc=p->caches[n]))
			{
				tc->frees++;
				RemoveCacheEntries(p, tc, 0);
				assert(!tc->freeInCache);
				tc->mymspace=-1;
				tc->threadid=0;
				mspace_free(0, tc);
				p->caches[n]=0;
			}
		}
	}
}