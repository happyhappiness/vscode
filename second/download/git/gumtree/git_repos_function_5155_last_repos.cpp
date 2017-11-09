static void write_tempfile_record(const char *name, const char *prefix)
{
	int i;

	if (CHECKOUT_ALL == checkout_stage) {
		for (i = 1; i < 4; i++) {
			if (i > 1)
				putchar(' ');
			if (topath[i][0])
				fputs(topath[i], stdout);
			else
				putchar('.');
		}
	} else
		fputs(topath[checkout_stage], stdout);

	putchar('\t');
	write_name_quoted_relative(name, prefix, stdout,
				   nul_term_line ? '\0' : '\n');

	for (i = 0; i < 4; i++) {
		topath[i][0] = 0;
	}
}