static inline int
isPrint(const char *ptr)
{
	return isprint(*(unsigned char *)ptr);
}