int u_strcmp(const char *cs1, const char *cs2)
{
	const uchar *s1 = (const uchar *)cs1;
	const uchar *s2 = (const uchar *)cs2;

	while (*s1 && *s2 && (*s1 == *s2)) {
		s1++; s2++;
	}

	return (int)*s1 - (int)*s2;
}