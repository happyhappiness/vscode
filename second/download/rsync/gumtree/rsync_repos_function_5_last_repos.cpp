void *_new_array(unsigned long num, unsigned int size, int use_calloc)
{
	if (num >= MALLOC_MAX/size)
		return NULL;
	return use_calloc ? calloc(num, size) : malloc(num * size);
}