static char *cut_ident_timestamp_part(char *string)
{
	char *ket = strrchr(string, '>');
	if (!ket || ket[1] != ' ')
		die(_("Malformed ident string: '%s'"), string);
	*++ket = '\0';
	return ket;
}