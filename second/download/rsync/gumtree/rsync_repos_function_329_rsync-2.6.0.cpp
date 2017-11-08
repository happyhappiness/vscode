char *find_colon(char *s)
{
	char *p, *p2;

	p = strchr(s,':');
	if (!p) return NULL;

	/* now check to see if there is a / in the string before the : - if there is then
	   discard the colon on the assumption that the : is part of a filename */
	p2 = strchr(s,'/');
	if (p2 && p2 < p) return NULL;

	return p;
}