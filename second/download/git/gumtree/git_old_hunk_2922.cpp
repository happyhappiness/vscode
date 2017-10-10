
	fprintf(stderr, "fast-import: dumping crash report to %s\n", loc);

	fprintf(rpt, "fast-import crash report:\n");
	fprintf(rpt, "    fast-import process: %"PRIuMAX"\n", (uintmax_t) getpid());
	fprintf(rpt, "    parent process     : %"PRIuMAX"\n", (uintmax_t) getppid());
	fprintf(rpt, "    at %s\n", show_date(time(NULL), 0, DATE_MODE(LOCAL)));
	fputc('\n', rpt);

	fputs("fatal: ", rpt);
	fputs(err, rpt);
	fputc('\n', rpt);

