void   nedpmalloc_stats(nedpool *p) THROWSPEC
{
	int n;
	if(!p) { p=&syspool; if(!syspool.threads) InitPool(&syspool, 0, -1); }
	for(n=0; p->m[n]; n++)
	{
		mspace_malloc_stats(p->m[n]);
	}
}