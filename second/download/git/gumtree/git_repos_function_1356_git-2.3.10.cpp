static inline int sane_iscase(int x, int is_lower)
{
	if (!sane_istest(x, GIT_ALPHA))
		return 0;

	if (is_lower)
		return (x & 0x20) != 0;
	else
		return (x & 0x20) == 0;
}