void *memmove(void *dest, const void *src, size_t n)
{
	memcpy(dest, src, n);
	return dest;
}