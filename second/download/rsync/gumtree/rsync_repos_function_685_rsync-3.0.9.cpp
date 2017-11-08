void *memmove(void *dest, const void *src, size_t n)
{
	bcopy((char *) src, (char *) dest, n);
	return dest;
}