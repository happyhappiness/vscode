static int strip_timestamp(char *bol, char **eol_p)
{
	char *eol = *eol_p;
	int ch;

	while (bol < --eol) {
		if (*eol != '>')
			continue;
		*eol_p = ++eol;
		ch = *eol;
		*eol = '\0';
		return ch;
	}
	return 0;
}