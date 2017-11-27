unsigned long long htonll (unsigned long long n)
{
#if __BYTE_ORDER == __BIG_ENDIAN
	return (n);
#else
	return (((unsigned long long) htonl (n)) << 32) + htonl (n >> 32);
#endif
}