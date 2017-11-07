int run_column_filter(int colopts, const struct column_options *opts)
{
	struct argv_array *argv;

	if (fd_out != -1)
		return -1;

	child_process_init(&column_process);
	argv = &column_process.args;

	argv_array_push(argv, "column");
	argv_array_pushf(argv, "--raw-mode=%d", colopts);
	if (opts && opts->width)
		argv_array_pushf(argv, "--width=%d", opts->width);
	if (opts && opts->indent)
		argv_array_pushf(argv, "--indent=%s", opts->indent);
	if (opts && opts->padding)
		argv_array_pushf(argv, "--padding=%d", opts->padding);

	fflush(stdout);
	column_process.in = -1;
	column_process.out = dup(1);
	column_process.git_cmd = 1;

	if (start_command(&column_process))
		return -2;

	fd_out = dup(1);
	close(1);
	dup2(column_process.in, 1);
	close(column_process.in);
	return 0;
}