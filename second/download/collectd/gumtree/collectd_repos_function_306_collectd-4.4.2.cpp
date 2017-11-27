int strsplit (char *string, char **fields, size_t size)
{
	size_t i;
	char *ptr;
	char *saveptr;

	i = 0;
	ptr = string;
	saveptr = NULL;
	while ((fields[i] = strtok_r (ptr, " \t\r\n", &saveptr)) != NULL)
	{
		ptr = NULL;
		i++;

		if (i >= size)
			break;
	}

	return (i);
}