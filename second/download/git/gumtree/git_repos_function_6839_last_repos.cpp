int    nedpmalloc_trim(nedpool *p, size_t pad) THROWSPEC
{
	int n, ret=0;
	if(!p) { p=&syspool; if(!syspool.threads) InitPool(&syspool, 0, -1); }
	for(n=0; p->m[n]; n++)
	{
		ret+=mspace_trim(p->m[n], pad);
	}
	return ret;
}