static int is_foreign_ident(const char *str)
{
	int i;

	if (!starts_with(str, "$Id: "))
		return 0;
	for (i = 5; str[i]; i++) {
		if (isspace(str[i]) && str[i+1] != '$')
			return 1;
	}
	return 0;
}