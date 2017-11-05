static int split_mbox(const char *file, const char *dir, int allow_bare,
		      int nr_prec, int skip)
{
	int ret = -1;
	int peek;

	FILE *f = !strcmp(file, "-") ? stdin : fopen(file, "r");
	int file_done = 0;

	if (!f) {
		error("cannot open mbox %s", file);
		goto out;
	}

	do {
		peek = fgetc(f);
	} while (isspace(peek));
	ungetc(peek, f);

	if (strbuf_getwholeline(&buf, f, '\n')) {
		/* empty stdin is OK */
		if (f != stdin) {
			error("cannot read mbox %s", file);
			goto out;
		}
		file_done = 1;
	}

	while (!file_done) {
		char *name = xstrfmt("%s/%0*d", dir, nr_prec, ++skip);
		file_done = split_one(f, name, allow_bare);
		free(name);
	}

	if (f != stdin)
		fclose(f);

	ret = skip;
out:
	return ret;
}