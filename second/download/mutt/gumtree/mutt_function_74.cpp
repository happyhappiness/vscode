void print_usage(const char *progname) {
	fprintf(stderr, "Command line usage: %s [flags] -- prefix [recipients]\n", progname);
	exit(1);
}