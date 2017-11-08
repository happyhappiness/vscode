static char *next_arg(char **s)
{
	char *ret;

	if (!s || !*s)
		return NULL;
	while (isspace((unsigned char) **s))
		(*s)++;
	if (!**s) {
		*s = NULL;
		return NULL;
	}
	if (**s == '"') {
		++*s;
		ret = *s;
		*s = strchr(*s, '"');
	} else {
		ret = *s;
		while (**s && !isspace((unsigned char) **s))
			(*s)++;
	}
	if (*s) {
		if (**s)
			*(*s)++ = 0;
		if (!**s)
			*s = NULL;
	}
	return ret;
}