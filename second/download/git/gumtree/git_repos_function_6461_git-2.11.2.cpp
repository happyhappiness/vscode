static NOINLINE void ReleaseFreeInCache(nedpool *p, threadcache *tc, int mymspace) THROWSPEC
{
	unsigned int age=THREADCACHEMAXFREESPACE/8192;
	/*ACQUIRE_LOCK(&p->m[mymspace]->mutex);*/
	while(age && tc->freeInCache>=THREADCACHEMAXFREESPACE)
	{
		RemoveCacheEntries(p, tc, age);
		/*printf("*** Removing cache entries older than %u (%u)\n", age, (unsigned int) tc->freeInCache);*/
		age>>=1;
	}
	/*RELEASE_LOCK(&p->m[mymspace]->mutex);*/
}