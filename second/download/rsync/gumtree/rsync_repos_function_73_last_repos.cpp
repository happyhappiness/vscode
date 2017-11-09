static inline int
isSpace(const char *ptr)
{
	return isspace(*(unsigned char *)ptr);
}