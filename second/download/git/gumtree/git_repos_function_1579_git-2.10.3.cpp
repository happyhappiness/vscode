static int parse_num(char **cp_p, int *num_p)
{
	char *cp = *cp_p;
	int num = 0;

	while ('0' <= *cp && *cp <= '9')
		num = num * 10 + *cp++ - '0';
	if (!(cp - *cp_p))
		return -1;
	*cp_p = cp;
	*num_p = num;
	return 0;
}