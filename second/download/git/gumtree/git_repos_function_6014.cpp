static NOINLINE void RemoveCacheEntries(nedpool *p, threadcache *tc, unsigned int age) THROWSPEC
{
#ifdef FULLSANITYCHECKS
	tcfullsanitycheck(tc);
#endif
	if(tc->freeInCache)
	{
		threadcacheblk **tcbptr=tc->bins;
		int n;
		for(n=0; n<=THREADCACHEMAXBINS; n++, tcbptr+=2)
		{
			threadcacheblk **tcb=tcbptr+1;		/* come from oldest end of list */
			/*tcsanitycheck(tcbptr);*/
			for(; *tcb && tc->frees-(*tcb)->lastUsed>=age; )
			{
				threadcacheblk *f=*tcb;
				size_t blksize=f->size; /*nedblksize(f);*/
				assert(blksize<=nedblksize(f));
				assert(blksize);
#ifdef FULLSANITYCHECKS
				assert(*(unsigned int *) "NEDN"==(*tcb)->magic);
#endif
				*tcb=(*tcb)->prev;
				if(*tcb)
					(*tcb)->next=0;
				else
					*tcbptr=0;
				tc->freeInCache-=blksize;
				assert((long) tc->freeInCache>=0);
				mspace_free(0, f);
				/*tcsanitycheck(tcbptr);*/
			}
		}
	}
#ifdef FULLSANITYCHECKS
	tcfullsanitycheck(tc);
#endif
}