static int is_foreign_ident(const char *str)
{
	int i;

	if (!skip_prefix(str, "$Id: ", &str))
		return 0;
	for (i = 0; str[i]; i++) {
		if (isspace(str[i]) && str[i+1] != '$')
			return 1;
	}
	return 0;
}