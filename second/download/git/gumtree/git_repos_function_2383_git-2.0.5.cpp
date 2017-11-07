static int names_conflict(const char *refname1, const char *refname2)
{
	for (; *refname1 && *refname1 == *refname2; refname1++, refname2++)
		;
	return (*refname1 == '\0' && *refname2 == '/')
		|| (*refname1 == '/' && *refname2 == '\0');
}