void neddestroypool(nedpool *p) THROWSPEC
{
	int n;
	ACQUIRE_LOCK(&p->mutex);
	DestroyCaches(p);
	for(n=0; p->m[n]; n++)
	{
		destroy_mspace(p->m[n]);
		p->m[n]=0;
	}
	RELEASE_LOCK(&p->mutex);
	if(TLSFREE(p->mycache)) abort();
	nedpfree(0, p);
}