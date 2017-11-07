static void print_tok_val(const char *tok, const char *val)
{
	char c = last_non_space_char(tok);
	if (!c)
		return;
	if (strchr(separators, c))
		printf("%s%s\n", tok, val);
	else
		printf("%s%c %s\n", tok, separators[0], val);
}