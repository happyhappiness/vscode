struct mallinfo nedpmallinfo(nedpool *p) THROWSPEC
{
	int n;
	struct mallinfo ret={0};
	if(!p) { p=&syspool; if(!syspool.threads) InitPool(&syspool, 0, -1); }
	for(n=0; p->m[n]; n++)
	{
		struct mallinfo t=mspace_mallinfo(p->m[n]);
		ret.arena+=t.arena;
		ret.ordblks+=t.ordblks;
		ret.hblkhd+=t.hblkhd;
		ret.usmblks+=t.usmblks;
		ret.uordblks+=t.uordblks;
		ret.fordblks+=t.fordblks;
		ret.keepcost+=t.keepcost;
	}
	return ret;
}