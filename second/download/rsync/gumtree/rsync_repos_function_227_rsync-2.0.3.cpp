void *memmove(void *dest, const void *src, size_t n)
{
	bcopy(src, dest, n);
	return dest;
}