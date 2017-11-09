static int cmp_icase(char a, char b)
{
	if (a == b)
		return 0;
	if (ignore_case)
		return toupper(a) - toupper(b);
	return a - b;
}