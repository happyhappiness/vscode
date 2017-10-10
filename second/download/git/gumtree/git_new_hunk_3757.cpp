	else
		return (char *)data + ends[line] + 1;
}

static void print_line(const char *prefix, char first,
		       long line, unsigned long *ends, void *data,
		       const char *color, const char *reset, FILE *file)
{
	char *begin = get_nth_line(line, ends, data);
	char *end = get_nth_line(line+1, ends, data);
	int had_nl = 0;

	if (end > begin && end[-1] == '\n') {
		end--;
		had_nl = 1;
	}

	fputs(prefix, file);
	fputs(color, file);
	putc(first, file);
	fwrite(begin, 1, end-begin, file);
	fputs(reset, file);
	putc('\n', file);
	if (!had_nl)
		fputs("\\ No newline at end of file\n", file);
}

static char *output_prefix(struct diff_options *opt)
{
	char *prefix = "";

