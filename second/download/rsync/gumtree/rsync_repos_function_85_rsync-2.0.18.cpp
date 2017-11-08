static int match_hostname(char *host, char *tok)
{
	if (!host || !*host) return 0;
	return (fnmatch(tok, host, 0) == 0);
}