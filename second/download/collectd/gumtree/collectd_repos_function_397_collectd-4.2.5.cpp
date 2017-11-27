static inline long long __get_sock_bytes(const char *s)
{
	while (s[0] != '/')
		++s;

	/* Remove '/' */
	++s;
	return atoll(s);
}