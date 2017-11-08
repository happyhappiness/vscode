static int str_isspace(const char *str)
{
	for (; *str; str++)
		if (!isspace(*str))
			return 0;

	return 1;
}