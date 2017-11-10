static char *squash_slash(char *name)
{
	int i = 0, j = 0;

	if (!name)
		return NULL;

	while (name[i]) {
		if ((name[j++] = name[i++]) == '/')
			while (name[i] == '/')
				i++;
	}
	name[j] = '\0';
	return name;
}