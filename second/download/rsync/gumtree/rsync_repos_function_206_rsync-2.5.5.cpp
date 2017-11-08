void *Realloc(void *p, int size)
{
	if (!p) return (void *)malloc(size);
	return (void *)realloc(p, size);
}