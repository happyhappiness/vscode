void *_new_array(unsigned int size, unsigned long num)
{
	if (num >= MALLOC_MAX/size)
		return NULL;
	return malloc(size * num);
}