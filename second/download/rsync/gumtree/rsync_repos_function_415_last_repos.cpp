int
main(int argc, char *argv[])
{
	poptContext pc;
	const char **extra_args;
	int opt;

	pc = poptGetContext(PROGRAM, argc, (const char **)argv,
			    long_options, 0);
	while ((opt = poptGetNextOpt(pc)) != -1) {
		switch (opt) {
		case 'h':
			tls_usage(0);
		default:
			fprintf(stderr,
			        "%s: %s\n",
				poptBadOption(pc, POPT_BADOPTION_NOALIAS),
				poptStrerror(opt));
			tls_usage(1);
		}
	}

	extra_args = poptGetArgs(pc);
	if (!extra_args || *extra_args == NULL)
		tls_usage(1);

	for (; *extra_args; extra_args++)
		list_file(*extra_args);
	poptFreeContext(pc);

	return 0;
}