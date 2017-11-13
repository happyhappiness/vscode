static void print_tok_val(FILE *outfile, const char *tok, const char *val)
{
	char c;

	if (!tok) {
		fprintf(outfile, "%s\n", val);
		return;
	}

	c = last_non_space_char(tok);
	if (!c)
		return;
	if (strchr(separators, c))
		fprintf(outfile, "%s%s\n", tok, val);
	else
		fprintf(outfile, "%s%c %s\n", tok, separators[0], val);
}