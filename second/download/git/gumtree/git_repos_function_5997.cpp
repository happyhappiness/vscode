size_t nedblksize(void *mem) THROWSPEC
{
#if 0
	/* Only enable if testing with valgrind. Causes misoperation */
	return THREADCACHEMAX;
#else
	if(mem)
	{
		mchunkptr p=mem2chunk(mem);
		assert(cinuse(p));	/* If this fails, someone tried to free a block twice */
		if(cinuse(p))
			return chunksize(p)-overhead_for(p);
	}
	return 0;
#endif
}