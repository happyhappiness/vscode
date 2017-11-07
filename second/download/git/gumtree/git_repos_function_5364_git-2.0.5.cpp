static FORCEINLINE mstate GetMSpace(nedpool *p, threadcache *tc, int mymspace, size_t size) THROWSPEC
{	/* Returns a locked and ready for use mspace */
	mstate m=p->m[mymspace];
	assert(m);
	if(!TRY_LOCK(&p->m[mymspace]->mutex)) m=FindMSpace(p, tc, &mymspace, size);\
	/*assert(IS_LOCKED(&p->m[mymspace]->mutex));*/
	return m;
}