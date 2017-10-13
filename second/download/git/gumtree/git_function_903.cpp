static void print_lines(FILE *outfile, struct strbuf **lines, int start, int end)
{
	int i;
	for (i = start; lines[i] && i < end; i++)
		fprintf(outfile, "%s", lines[i]->buf);
}