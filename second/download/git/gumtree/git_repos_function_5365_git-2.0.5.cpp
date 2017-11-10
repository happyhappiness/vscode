static FORCEINLINE void GetThreadCache(nedpool **p, threadcache **tc, int *mymspace, size_t *size) THROWSPEC
{
	int mycache;
	if(size && *size<sizeof(threadcacheblk)) *size=sizeof(threadcacheblk);
	if(!*p)
	{
		*p=&syspool;
		if(!syspool.threads) InitPool(&syspool, 0, -1);
	}
	mycache=(int)(size_t) TLSGET((*p)->mycache);
	if(mycache>0)
	{
		*tc=(*p)->caches[mycache-1];
		*mymspace=(*tc)->mymspace;
	}
	else if(!mycache)
	{
		*tc=AllocCache(*p);
		if(!*tc)
		{	/* Disable */
			if(TLSSET((*p)->mycache, (void *)-1)) abort();
			*mymspace=0;
		}
		else
			*mymspace=(*tc)->mymspace;
	}
	else
	{
		*tc=0;
		*mymspace=-mycache-1;
	}
	assert(*mymspace>=0);
	assert((long)(size_t)CURRENT_THREAD==(*tc)->threadid);
#ifdef FULLSANITYCHECKS
	if(*tc)
	{
		if(*(unsigned int *)"NEDMALC1"!=(*tc)->magic1 || *(unsigned int *)"NEDMALC2"!=(*tc)->magic2)
		{
			abort();
		}
	}
#endif
}