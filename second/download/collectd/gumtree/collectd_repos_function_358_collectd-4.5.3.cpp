int strsubstitute (char *str, char c_from, char c_to)
{
	int ret;

	if (str == NULL)
		return (-1);

	ret = 0;
	while (*str != '\0')
	{
		if (*str == c_from)
		{
			*str = c_to;
			ret++;
		}
		str++;
	}

	return (ret);
}