static int strwicmp(char *psz1, char *psz2)
{
	/* if BOTH strings are NULL, return TRUE, if ONE is NULL return */
	/* appropriate value. */
	if (psz1 == psz2)
		return 0;

	if (psz1 == NULL)
		return -1;

	if (psz2 == NULL)
		return 1;

	/* sync the strings on first non-whitespace */
	while (1) {
		while (isSpace(psz1))
			psz1++;
		while (isSpace(psz2))
			psz2++;
		if (toUpper(psz1) != toUpper(psz2) || *psz1 == '\0' || *psz2 == '\0')
			break;
		psz1++;
		psz2++;
	}
	return *psz1 - *psz2;
}