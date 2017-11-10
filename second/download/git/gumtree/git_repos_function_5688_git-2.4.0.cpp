static void threadcache_free(nedpool *p, threadcache *tc, int mymspace, void *mem, size_t size) THROWSPEC
{
	unsigned int bestsize;
	unsigned int idx=size2binidx(size);
	threadcacheblk **binsptr, *tck=(threadcacheblk *) mem;
	assert(size>=sizeof(threadcacheblk) && size<=THREADCACHEMAX+CHUNK_OVERHEAD);
#ifdef DEBUG
	{	/* Make sure this is a valid memory block */
	    mchunkptr p  = mem2chunk(mem);
	    mstate fm = get_mstate_for(p);
	    if (!ok_magic(fm)) {
	      USAGE_ERROR_ACTION(fm, p);
	      return;
	    }
	}
#endif
#ifdef FULLSANITYCHECKS
	tcfullsanitycheck(tc);
#endif
	/* Calculate best fit bin size */
	bestsize=1<<(idx+4);
#if 0
	/* Finer grained bin fit */
	idx<<=1;
	if(size>bestsize)
	{
		unsigned int biggerbestsize=bestsize+bestsize<<1;
		if(size>=biggerbestsize)
		{
			idx++;
			bestsize=biggerbestsize;
		}
	}
#endif
	if(bestsize!=size)	/* dlmalloc can round up, so we round down to preserve indexing */
		size=bestsize;
	binsptr=&tc->bins[idx*2];
	assert(idx<=THREADCACHEMAXBINS);
	if(tck==*binsptr)
	{
		fprintf(stderr, "Attempt to free already freed memory block %p - aborting!\n", tck);
		abort();
	}
#ifdef FULLSANITYCHECKS
	tck->magic=*(unsigned int *) "NEDN";
#endif
	tck->lastUsed=++tc->frees;
	tck->size=(unsigned int) size;
	tck->next=*binsptr;
	tck->prev=0;
	if(tck->next)
		tck->next->prev=tck;
	else
		binsptr[1]=tck;
	assert(!*binsptr || (*binsptr)->size==tck->size);
	*binsptr=tck;
	assert(tck==tc->bins[idx*2]);
	assert(tc->bins[idx*2+1]==tck || binsptr[0]->next->prev==tck);
	/*printf("free: %p, %p, %p, %lu\n", p, tc, mem, (long) size);*/
	tc->freeInCache+=size;
#ifdef FULLSANITYCHECKS
	tcfullsanitycheck(tc);
#endif
#if 1
	if(tc->freeInCache>=THREADCACHEMAXFREESPACE)
		ReleaseFreeInCache(p, tc, mymspace);
#endif
}