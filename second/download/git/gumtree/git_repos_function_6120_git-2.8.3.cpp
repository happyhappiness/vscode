static void *threadcache_malloc(nedpool *p, threadcache *tc, size_t *size) THROWSPEC
{
	void *ret=0;
	unsigned int bestsize;
	unsigned int idx=size2binidx(*size);
	size_t blksize=0;
	threadcacheblk *blk, **binsptr;
#ifdef FULLSANITYCHECKS
	tcfullsanitycheck(tc);
#endif
	/* Calculate best fit bin size */
	bestsize=1<<(idx+4);
#if 0
	/* Finer grained bin fit */
	idx<<=1;
	if(*size>bestsize)
	{
		idx++;
		bestsize+=bestsize>>1;
	}
	if(*size>bestsize)
	{
		idx++;
		bestsize=1<<(4+(idx>>1));
	}
#else
	if(*size>bestsize)
	{
		idx++;
		bestsize<<=1;
	}
#endif
	assert(bestsize>=*size);
	if(*size<bestsize) *size=bestsize;
	assert(*size<=THREADCACHEMAX);
	assert(idx<=THREADCACHEMAXBINS);
	binsptr=&tc->bins[idx*2];
	/* Try to match close, but move up a bin if necessary */
	blk=*binsptr;
	if(!blk || blk->size<*size)
	{	/* Bump it up a bin */
		if(idx<THREADCACHEMAXBINS)
		{
			idx++;
			binsptr+=2;
			blk=*binsptr;
		}
	}
	if(blk)
	{
		blksize=blk->size; /*nedblksize(blk);*/
		assert(nedblksize(blk)>=blksize);
		assert(blksize>=*size);
		if(blk->next)
			blk->next->prev=0;
		*binsptr=blk->next;
		if(!*binsptr)
			binsptr[1]=0;
#ifdef FULLSANITYCHECKS
		blk->magic=0;
#endif
		assert(binsptr[0]!=blk && binsptr[1]!=blk);
		assert(nedblksize(blk)>=sizeof(threadcacheblk) && nedblksize(blk)<=THREADCACHEMAX+CHUNK_OVERHEAD);
		/*printf("malloc: %p, %p, %p, %lu\n", p, tc, blk, (long) size);*/
		ret=(void *) blk;
	}
	++tc->mallocs;
	if(ret)
	{
		assert(blksize>=*size);
		++tc->successes;
		tc->freeInCache-=blksize;
		assert((long) tc->freeInCache>=0);
	}
#if defined(DEBUG) && 0
	if(!(tc->mallocs & 0xfff))
	{
		printf("*** threadcache=%u, mallocs=%u (%f), free=%u (%f), freeInCache=%u\n", (unsigned int) tc->threadid, tc->mallocs,
			(float) tc->successes/tc->mallocs, tc->frees, (float) tc->successes/tc->frees, (unsigned int) tc->freeInCache);
	}
#endif
#ifdef FULLSANITYCHECKS
	tcfullsanitycheck(tc);
#endif
	return ret;
}