	else
		return (char *)data + ends[line] + 1;
}

static void print_line(const char *prefix, char first,
		       long line, unsigned long *ends, void *data,
		       const char *color, const char *reset)
{
	char *begin = get_nth_line(line, ends, data);
	char *end = get_nth_line(line+1, ends, data);
	int had_nl = 0;

	if (end > begin && end[-1] == '\n') {
		end--;
		had_nl = 1;
	}

	fputs(prefix, stdout);
	fputs(color, stdout);
	putchar(first);
	fwrite(begin, 1, end-begin, stdout);
	fputs(reset, stdout);
	putchar('\n');
	if (!had_nl)
		fputs("\\ No newline at end of file\n", stdout);
}

static char *output_prefix(struct diff_options *opt)
{
	char *prefix = "";

