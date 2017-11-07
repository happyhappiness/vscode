static void print_ref_status(char flag, const char *summary, struct ref *to, struct ref *from, const char *msg, int porcelain)
{
	if (porcelain) {
		if (from)
			fprintf(stdout, "%c\t%s:%s\t", flag, from->name, to->name);
		else
			fprintf(stdout, "%c\t:%s\t", flag, to->name);
		if (msg)
			fprintf(stdout, "%s (%s)\n", summary, msg);
		else
			fprintf(stdout, "%s\n", summary);
	} else {
		fprintf(stderr, " %c %-*s ", flag, TRANSPORT_SUMMARY_WIDTH, summary);
		if (from)
			fprintf(stderr, "%s -> %s", prettify_refname(from->name), prettify_refname(to->name));
		else
			fputs(prettify_refname(to->name), stderr);
		if (msg) {
			fputs(" (", stderr);
			fputs(msg, stderr);
			fputc(')', stderr);
		}
		fputc('\n', stderr);
	}
}