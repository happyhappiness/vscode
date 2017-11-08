void *_realloc_array(void *ptr, unsigned int size, size_t num)
{
	if (num >= MALLOC_MAX/size)
		return NULL;
	if (!ptr)
		return malloc(size * num);
	return realloc(ptr, size * num);
}