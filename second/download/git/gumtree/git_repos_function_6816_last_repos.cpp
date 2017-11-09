static void tcfullsanitycheck(threadcache *tc) THROWSPEC
{
	threadcacheblk **tcbptr=tc->bins;
	int n;
	for(n=0; n<=THREADCACHEMAXBINS; n++, tcbptr+=2)
	{
		threadcacheblk *b, *ob=0;
		tcsanitycheck(tcbptr);
		for(b=tcbptr[0]; b; ob=b, b=b->next)
		{
			assert(*(unsigned int *) "NEDN"==b->magic);
			assert(!ob || ob->next==b);
			assert(!ob || b->prev==ob);
		}
	}
}