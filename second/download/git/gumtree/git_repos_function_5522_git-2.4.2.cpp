static __inline int strcasecmp (const char *s1, const char *s2)
{
	int size1 = strlen(s1);
	int sisz2 = strlen(s2);
	return _strnicmp(s1, s2, sisz2 > size1 ? sisz2 : size1);
}