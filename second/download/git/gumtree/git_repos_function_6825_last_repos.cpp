nedpool *nedcreatepool(size_t capacity, int threads) THROWSPEC
{
	nedpool *ret;
	if(!(ret=(nedpool *) nedpcalloc(0, 1, sizeof(nedpool)))) return 0;
	if(!InitPool(ret, capacity, threads))
	{
		nedpfree(0, ret);
		return 0;
	}
	return ret;
}