static void print_lines(struct strbuf **lines, int start, int end)
{
	int i;
	for (i = start; lines[i] && i < end; i++)
		printf("%s", lines[i]->buf);
}