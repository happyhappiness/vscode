static int get_line (char *s, int n)
{
    char *cp;

    if (!fgets(s, n, stdin))
	return (0);
    cp = strchr(s, '\n');
    if (cp)
	*cp = '\0';
    return (1);
}