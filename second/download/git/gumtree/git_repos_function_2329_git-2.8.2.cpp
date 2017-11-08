void write_name_quoted(const char *name, FILE *fp, int terminator)
{
	if (terminator) {
		quote_c_style(name, NULL, fp, 0);
	} else {
		fputs(name, fp);
	}
	fputc(terminator, fp);
}