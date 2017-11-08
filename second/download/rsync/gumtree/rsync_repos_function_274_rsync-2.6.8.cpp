void *_realloc_array(void *ptr, unsigned int size, unsigned long num)
{
	if (num >= MALLOC_MAX/size)
		return NULL;
	/* No realloc should need this, but just in case... */
	if (!ptr)
		return malloc(size * num);
	return realloc(ptr, size * num);
}