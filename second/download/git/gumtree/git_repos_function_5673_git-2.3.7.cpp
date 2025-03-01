static NOINLINE mstate FindMSpace(nedpool *p, threadcache *tc, int *lastUsed, size_t size) THROWSPEC
{	/* Gets called when thread's last used mspace is in use. The strategy
	is to run through the list of all available mspaces looking for an
	unlocked one and if we fail, we create a new one so long as we don't
	exceed p->threads */
	int n, end;
	for(n=end=*lastUsed+1; p->m[n]; end=++n)
	{
		if(TRY_LOCK(&p->m[n]->mutex)) goto found;
	}
	for(n=0; n<*lastUsed && p->m[n]; n++)
	{
		if(TRY_LOCK(&p->m[n]->mutex)) goto found;
	}
	if(end<p->threads)
	{
		mstate temp;
		if(!(temp=(mstate) create_mspace(size, 1)))
			goto badexit;
		/* Now we're ready to modify the lists, we lock */
		ACQUIRE_LOCK(&p->mutex);
		while(p->m[end] && end<p->threads)
			end++;
		if(end>=p->threads)
		{	/* Drat, must destroy it now */
			RELEASE_LOCK(&p->mutex);
			destroy_mspace((mspace) temp);
			goto badexit;
		}
		/* We really want to make sure this goes into memory now but we
		have to be careful of breaking aliasing rules, so write it twice */
		{
			volatile struct malloc_state **_m=(volatile struct malloc_state **) &p->m[end];
			*_m=(p->m[end]=temp);
		}
		ACQUIRE_LOCK(&p->m[end]->mutex);
		/*printf("Created mspace idx %d\n", end);*/
		RELEASE_LOCK(&p->mutex);
		n=end;
		goto found;
	}
	/* Let it lock on the last one it used */
badexit:
	ACQUIRE_LOCK(&p->m[*lastUsed]->mutex);
	return p->m[*lastUsed];
found:
	*lastUsed=n;
	if(tc)
		tc->mymspace=n;
	else
	{
		if(TLSSET(p->mycache, (void *)(size_t)(-(n+1)))) abort();
	}
	return p->m[n];
}